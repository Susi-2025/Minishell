/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdohanic <cdohanic@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 18:58:03 by cdohanic          #+#    #+#             */
/*   Updated: 2025/08/16 17:46:20 by cdohanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>


typedef struct s_simple_cmd 
{
	int 	args_capacity;
	int		args_count;
	char	**args;
} t_simple_cmd;

typedef struct s_cmd
{
	int cmds_capacity;
	int cmds_count;
	t_simple_cmd **simple_cmds;
	char	*out_file;
	char	*in_file;
	char	*err_file;
	char	*here_doc;
	char	*file_append;
}	t_cmd;

typedef enum {
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	TOKEN_EOF,
}	t_token_type;
//grep -a lsd > outfile = [WORD WORD WORD REDIR_IN WORD]
typedef struct {
	t_token_type	type;
	char			*value;
}	t_token;

int	is_space(char c)
{
	int		i;
	char	spaces[] = {' ', '\t', '\r', '\n', '\v', '\0'};
	i = 0;
	while (spaces[i])
	{
		if (c == spaces[i])
			return (1);
		i++;
	}
	return (0);
}

int is_delimiter(char c)
{
	int		i;
	char	delimiters[] = {'|', '<', '>', '\0'};
	i = 0;
	while (delimiters[i])
	{
		if (c == delimiters[i])
			return (1);
		i++;
	}
	return (0);
}

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size > 0)
	{
		while (i < size - 1 && src[i] != '\0')
		{
			dst[i] = src[i];
			i++;
		}
	}
	if (i < size)
		dst[i] = '\0';
	while (src[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup(const char *s)
{
	char	*dst;
	int		i;

	i = 0;
	dst = (char *)malloc(ft_strlen(s) + 1);
	if (dst == NULL)
		return (NULL);
	while (s[i])
	{
		dst[i] = s[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

t_token	*tokenize(char *l, int *token_count)
{
	int		i;
	int		count;
	t_token	*tokens;

	count = 0;
	i = 0;
	tokens = malloc(sizeof(t_token) * 100);

	if (!tokens)
		return (NULL);
	while (l[i])
	{
		while (l[i] && is_space(l[i]))
			i++;
		if (!l[i])
			break ;
		if (l[i] == '<')
		{
			tokens[count].type = REDIR_IN;
			tokens[count].value = ft_strdup("<");
			count++;
			i++;
		}
		else if (l[i] == '>')
		{
			if (l[i + 1] == '>')
			{
				tokens[count].type = REDIR_APPEND;
				tokens[count].value = ft_strdup(">>");
				i += 2;
			}
			else
			{
				tokens[count].type = REDIR_OUT;
				tokens[count].value = ft_strdup(">");
				i++;
			}
			count++;
		}
		else if (l[i] == '|')
		{
			tokens[count].type = PIPE;
			tokens[count].value = ft_strdup("|");
			count++;
			i++;
		}
		else
		{
			int start = i;
			while(l[i] && !is_space(l[i]) && !is_delimiter(l[i]))
				i++;
			int len = i - start;
			if (len > 0)
			{
				tokens[count].type = WORD;
				tokens[count].value = malloc(len + 1);
				if (tokens[count].value)
				{
					ft_strlcpy(tokens[count].value, l + start, len + 1);
				}
				count++;
			}
		}
	}
	tokens[count].type = TOKEN_EOF;
	tokens[count].value = NULL;
	count++;
	*token_count = count;
	return (tokens);
}

int	cmd_init(t_cmd *cmds)
{

    cmds->cmds_capacity = 2;
    cmds->cmds_count = 0;
    cmds->simple_cmds = malloc(sizeof(t_simple_cmd *) * cmds->cmds_capacity);
    cmds->in_file = NULL;
    cmds->out_file = NULL;
    cmds->err_file = NULL;
    cmds->here_doc = NULL;
    cmds->file_append = NULL;
    
    if (!cmds->simple_cmds)
		return (-1);
	return (0);
}

t_cmd	*parse_tokens(t_token *tokens, int token_count)
{
	t_cmd			*cmds;
	int				i;
	t_simple_cmd	*current_cmd;

	cmds = malloc(sizeof(t_cmd));
	if (!cmds)
		return (NULL);
	if (cmd_init(cmds) == -1)
		return (free(cmds), NULL);
	current_cmd = NULL;
	i = 0;
	while (i < token_count && tokens[i].type != TOKEN_EOF)
	{
		if (tokens[i].type == WORD)
		{
			if (!current_cmd)
			{
				if (cmds->cmds_count >= cmds->cmds_capacity)
				{
					cmds->cmds_capacity *= 2;
					cmds->simple_cmds = realloc(cmds->simple_cmds, sizeof(t_simple_cmd) * cmds->cmds_capacity);
				}
				current_cmd = malloc(sizeof(t_simple_cmd));
				current_cmd->args_capacity = 4;
				current_cmd->args_count = 0;
				current_cmd->args = malloc(sizeof(char *) * current_cmd->args_capacity);
				cmds->simple_cmds[cmds->cmds_count] = current_cmd;
				cmds->cmds_count++;
			}
			if (current_cmd->args_count >= current_cmd->args_capacity - 1)
			{
				current_cmd->args_capacity *= 2;
				current_cmd->args = realloc(current_cmd->args, sizeof(char *) * current_cmd->args_capacity);
			}
			current_cmd->args[current_cmd->args_count] = ft_strdup(tokens[i].value);
			current_cmd->args_count++;
			current_cmd->args[current_cmd->args_count] = NULL;
		}
		else if (tokens[i].type == REDIR_IN)
		{
			i++;
			if (i < token_count && tokens[i].type == WORD)
			{
				free(cmds->in_file);
				cmds->in_file = ft_strdup(tokens[i].value);
			}
		}
		else if (tokens[i].type == REDIR_OUT)
		{
			i++;
			if (i< token_count && tokens[i].type == WORD)
			{
				free(cmds->out_file);
				cmds->out_file = ft_strdup(tokens[i].value);
			}
		}
		else if (tokens[i].type == REDIR_APPEND)
		{
			i++;
			if (i< token_count && tokens[i].type == WORD)
			{
				free(cmds->file_append);
				cmds->file_append = ft_strdup(tokens[i].value);
			}
		}
		else if (tokens[i].type == PIPE)
		{
			current_cmd = NULL;
		}
		i++;
	}
	return (cmds);
}

void	free_tokens(t_token *tokens, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(tokens[i].value);
		i++;
	}
	free(tokens);
}

t_cmd	*ft_lex(char *line)
{
	int		token_count;
	t_token	*tokens;
	t_cmd	*cmds;

	tokens = tokenize(line, &token_count);
	if	(!tokens)
		return (NULL);
	cmds = parse_tokens(tokens, token_count);
	free_tokens(tokens, token_count);
	return (cmds);
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
	word = malloc(len + 1);
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

void	free_cmd(t_cmd *cmds)
{
	int	i;
	int	j;

	if (!cmds)
		return ;
	i = 0;
	while (i < cmds->cmds_count)
	{
		if (cmds->simple_cmds[i])
		{
			j = 0;
			while (j < cmds->simple_cmds[i]->args_count)
			{
				free(cmds->simple_cmds[i]->args[j]);
				j++;
			}
			free(cmds->simple_cmds[i]->args);
			free(cmds->simple_cmds[i]);
		}
		i++;
	}
    free(cmds->simple_cmds);
    free(cmds->in_file);
    free(cmds->out_file);
    free(cmds->err_file);
    free(cmds->here_doc);
    free(cmds->file_append);
    free(cmds);
}

int	main(void)
{
	char 	*rl;
	t_cmd 	*cmds;
	int		i;
	int		j;

	while (1)
	{
		rl = readline("Prompt: ");
		if (!rl)
			break ;
		if (*rl)
			add_history(rl);

		cmds = ft_lex(rl);
		if (cmds)
		{
		//	printf("Input: %s\n", rl);
			if (cmds->in_file)
				printf("Input file: %s\n", cmds->in_file);
			if (cmds->out_file)
				printf("Output file: %s\n", cmds->out_file);
			if (cmds->file_append)
				printf("Append file: %s\n", cmds->file_append);
			
			printf("Commands found: %d\n", cmds->cmds_count);
			i = 0;
			while (i < cmds->cmds_count)
			{
				j = 0;
				printf("Command %d: ", i);
				while (j < cmds->simple_cmds[i]->args_count)
				{
					printf("%s ", cmds->simple_cmds[i]->args[j]);
					j++;
				}
				i++;
				printf("\n");
			}
			free_cmd(cmds);
		}
		free(rl);
	}
	return (0);
}
