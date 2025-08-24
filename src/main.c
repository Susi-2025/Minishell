/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdohanic <cdohanic@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 18:58:03 by cdohanic          #+#    #+#             */
/*   Updated: 2025/08/22 11:14:14 by cdohanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

t_cmd	*ft_prepare_command(char *line, char *env[])
{
	int		token_count;
	t_token	*tokens;
	t_cmd	*cmds;

	tokens = tokenize(line, &token_count);
	if	(!tokens)
		return (NULL);
	cmds = parse_tokens(tokens, token_count, env);
	free_tokens(tokens, token_count);
	return (cmds);
}

// to do next time:
//DONE	-expand variables: retrieve from env the value of a variable or from local set 
//DONE	-variable expansion delimiters (az AZ 09)
// -go through the code. Find memory leaks/ vulnerabilities/ possible improvements
// CHECKED: expand_var, expand_end;
// 		- parse_word and rest linked to it
//		- parse_redir
//		- parse_tokenization
// -handle quotes: tokenize as word, parse the token
//	QUOTES: they create a single string with whatever is between them
//			- | << >> lose meaning. There is only 1 string between quotes
int	main(int argc, char *argv[], char *env[])
{
	char 	*rl;
	t_cmd 	*cmds;
	int		i;
	int		j;

	(void)argc;
	(void)argv;
	while (1)
	{
		rl = readline("Prompt: ");
		if (!rl)
			break ;
		if (*rl)
			add_history(rl);

		cmds = ft_prepare_command(rl, env);
		if (cmds)
		{
		//	printf("Input: %s\n", rl);
			if (cmds->in_file)
				printf("Input file: %s\n", cmds->in_file);
			if (cmds->out_file)
				printf("Output file: %s\n", cmds->out_file);
			if (cmds->file_append)
				printf("Append file: %s\n", cmds->file_append);
			if (cmds->here_doc)
				printf("Here_Doc: %s\n", cmds->here_doc);
			
			printf("Commands found: %d\n", cmds->cmds_count);
			i = 0;
			while (i < cmds->cmds_count)
			{
				j = 0;
				printf("Command %d: ", i + 1);
				while (j < cmds->simple_cmds[i]->args_count)
				{
					printf("%s ",cmds->simple_cmds[i]->args[j]);
					j++;
				}
				i++;
				printf("\n");
			}
			free_cmd(cmds);
		}
		free(rl);
	}
	rl_clear_history(); 
	return (0);
}

//TECHNICALLY USELESS
/*
int	count_words_until_delimiter(char *line)
{
	int	count;
	int	i;
	int in_word;

	count = 0;
	in_word = 0;
	i = 0;
	while (line[i] && line[i] != '>' && line[i] != '<' && line[i] != '|')
	{
		if  (line[i] != ' ' && !in_word)
		{
			count++;
			in_word = 1;
		}
		else if (line[i] == ' ')
			in_word = 0;
		i++;
	}
	return (count);
}

char	*extract_word(char *line, int *pos)
{
	int 	start;
	int		len;
	char	*word;

	while (line[*pos] && line[*pos] == ' ')
		(*pos)++;
	start = *pos;
	len = 0;
	while (line[*pos] && line[*pos] != ' ' && line[*pos] != '>' && line[*pos] != '<' &&  line[*pos] != '|')
	{
		len++;
		(*pos)++;
	}
	if (len == 0)
		return (NULL);
	word = malloc(len + 1);**args
	if (!word)
		return (NULL);

	strncpy(word, line + start, len);
	word[len] = '\0';

	return (word);
}

t_simple_cmd	*ft_create_sc(char *line, int *consumed)
{
	t_simple_cmd	*new_cmd;
	int	pos;

	pos = 0;
	new_cmd = malloc(sizeof(t_simple_cmd));
	if (!new_cmd)
		return (NULL);
	new_cmd->args_count = 0;
	new_cmd->args_capacity = count_words_until_delimiter(line);
	if (new_cmd->args_capacity == 0)
	{
		free(new_cmd);
		return (NULL);
	}
	new_cmd->args = (char **)malloc(sizeof(char *) * (new_cmd->args_capacity + 1));
	if (!new_cmd->args)
		return (free(new_cmd), NULL);
	while (new_cmd->args_count < new_cmd->args_capacity)
	{
		new_cmd->args[new_cmd->args_count] = extract_word(line, &pos);
		if (!new_cmd->args[new_cmd->args_count])
			break ;
		new_cmd->args_count++;
	}
	new_cmd->args[new_cmd->args_count] = NULL;
	*consumed = pos;
	return (new_cmd);
}

t_cmd	*ft_lex(char *line)
{
	int		i;
	int		j;
	char	in_file[1024];
	char	out_file[1024];
	t_cmd	*cmds;
	int		consumed;

	i = 0;
	cmds = malloc(sizeof(t_cmd));
	if (!cmds)
		return (NULL);
	cmds->cmds_capacity = 2;
	cmds->cmds_count = 0;
	cmds->simple_cmds = malloc(sizeof(t_simple_cmd *) * cmds->cmds_capacity);
	if (!cmds->simple_cmds)
	{
		free(cmds);
		return (NULL);
	}
	cmds->in_file = NULL;
	cmds->out_file = NULL;
	cmds->err_file = NULL;
	cmds->here_doc = NULL;
	cmds->file_append = NULL;
	while (line[i] != '\0')
	{
		 while (line[i] == ' ')
			 i++;
		 if (line[i] == '\0')
			 break ;
		 if (line[i] == '<')
		 {
			 i++;
			 j = 0;
			 while (line[i] == ' ')
				 i++;
			 while (line[i] && line[i] != ' ' && line[i] != '>')
			 {
				 in_file[j++] = line[i++];
				 if (j == 1023)
					 break ;
			 }
			 in_file[j] = '\0';
			 cmds->in_file = strdup(in_file);
		 }
		 else if (line[i] == '>')
		 {
			 i++;
			 j = 0;
			 while (line[i] == ' ')
				 i++;
			 while (line[i] && line[i] != ' ' && line[i] != '<')
			 {
				 out_file[j++] = line[i++];
				 if (j == 1023)
					 break ;
			 }
			 out_file[j] = '\0';
			 cmds->out_file = strdup(out_file);
		 }
		 else if (line[i] == '|')
		 {
			 i++;
		 }
		 else if (line[i] != ' ')
		 {
			 consumed = 0;
			 cmds->simple_cmds[cmds->cmds_count] = ft_create_sc(line + i, &consumed);
			 if (cmds->simple_cmds[cmds->cmds_count])
			 	cmds->cmds_count++;
			 i += consumed;
		 }
	}
	return (cmds);
}
*/
//ABOVE TECHNICALLY USELESS
