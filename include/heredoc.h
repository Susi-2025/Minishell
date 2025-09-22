
#ifndef HEREDOC_H
# define HEREDOC_H

# include "heredoc.h"
// heredoc
int	heredoc(t_cmd *cmds, char **env[], char **args, int args_count);
int	join_and_free(char **output, char *input);
void	init_pipe_heredoc(t_pipe_simple *pipex);
int	open_pipe_heredoc(t_pipe_simple *pipex);
void	connect_pipe_heredoc(t_pipe_simple *pipex);

#endif