/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vinguyen <vinguyen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 13:07:07 by cdohanic          #+#    #+#             */
/*   Updated: 2025/10/23 20:41:10 by vinguyen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t	g_interactive;

static int	is_delimiter_heredoc(char *input, char *del)
{
	if ((ft_strcmp(input, del) == 0) && (ft_strlen(input) == ft_strlen(del)))
	{
		return (1);
	}
	return (0);
}

static int	heredoc_read_loop(int fd, char *del, int quote_found, t_cmd *cmds)
{
	char	*input;

	while (1)
	{
		input = readline("> ");
		if (!input)
		{
			ft_putstr_fd("minishell: warning: here-document delimited"
							" by end-of-file\n",
							2);
			return (-1);
		}
		if (is_delimiter_heredoc(input, del))
		{
			free(input);
			return (0);
		}
		if (quote_found)
			input = parse_heredoc(input, cmds->envp, cmds->err_code);
		write(fd, input, ft_strlen(input));
		write(fd, "\n", 1);
		free(input);
	}
	return (0);
}

int	read_heredoc_to_file(char *del, char *filename, t_cmd *cmds, int *e_code)
{
	int	fd;
	int	quote_found;
	int	loop_status;

	quote_found = contains_quotes(del);
	if (quote_found == -1)
		return (-1);
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (-1);
	g_interactive = 2;
	setup_heredoc_signals();
	loop_status = heredoc_read_loop(fd, del, quote_found, cmds);
	reset_signals();
	g_interactive = 0;
	if (loop_status == -1)
	{
		close(fd);
		*e_code = 130;
		unlink(filename);
		return (-1);
	}
	close(fd);
	return (0);
}

char	*create_heredoc_file(void)
{
	static unsigned int	file_counter;
	const char			*path_start = ".here_doc";
	char				*temp_num;
	char				*path;

	path = NULL;
	while (path == NULL)
	{
		temp_num = ft_itoa(file_counter);
		file_counter++;
		if (!temp_num)
			return (NULL);
		path = ft_strjoin(path_start, temp_num);
		free(temp_num);
		if (!path)
			return (NULL);
		if (access(path, F_OK) == 0)
		{
			free(path);
			path = NULL;
			continue ;
		}
	}
	return (path);
}

int	handle_heredoc(t_cmd *cmds, char *del, int *error_code)
{
	char	*filename;

	filename = create_heredoc_file();
	if (!filename)
		return (-1);
	if (read_heredoc_to_file(del, filename, cmds, error_code) == -1)
	{
		free(filename);
		return (-1);
	}
	if (vector_push_back(cmds->heredoc_files, filename) == VECTOR_ERROR)
	{
		free(filename);
		return (-1);
	}
	return (0);
}
