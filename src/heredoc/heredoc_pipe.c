
#include "minishell.h"

void	init_pipe_heredoc(t_pipe_simple *pipex)
{
	pipex->infile_fd = -1;
	pipex->outfile_fd = -1;
}

int	open_pipe_heredoc(t_pipe_simple *pipex)
{
	if (pipe(pipex->pipefd) == -1)
    {
        perror("pipe");
        return (1);
    }
    pipex->pid = fork();
    if (pipex->pid == -1)
	{
        perror("fork");
        return (1);
	}
	return (0);
}

void	connect_pipe_heredoc(t_pipe_simple *pipex)
{
	close(pipex->pipefd[1]); // close write end
    dup2(pipex->pipefd[0], STDIN_FILENO); // redirect stdin
    close(pipex->pipefd[0]);
}