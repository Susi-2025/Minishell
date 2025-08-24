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

volatile sig_atomic_t g_interactive = 1;

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

void	handle_sigint(int sig)
{
	(void)sig;
	if (g_interactive)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	handle_sigquit(int sig)
{
	(void)sig;
	if (g_interactive)
		return;
}

void	setup_signals(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sa_int.sa_handler = handle_sigint;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa_int, NULL);

	sa_quit.sa_handler = handle_sigquit;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sa_quit, NULL);
}

int	main(int argc, char *argv[], char *env[])
{
	char 	*rl;
	t_cmd 	*cmds;
	int		i;
	int		j;

	(void)argc;
	(void)argv;
	setup_signals();
	while (1)
	{		
		g_interactive = 1;
		rl = readline("Prompt: ");
		if (!rl)
		{
			printf("exit\n");
			break ;
		}

		if (*rl)
			add_history(rl);

		g_interactive = 0;
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