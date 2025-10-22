
#include "minishell.h"

void	handle_no_file(t_cmd *cmds, char *arg, char *env[], int exit_code)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd( arg, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	free_and_exit(cmds, env, exit_code);
	// exit(code);
}

void	handle_cmd_error(t_cmd *cmds, char *arg, char *env[], int exit_code)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd( arg, 2);
	ft_putstr_fd(": command not found\n", 2);
	free_and_exit(cmds, env, exit_code);
	// exit(code);
}

// void	handle_envp_error(t_cmd *cmds, char *arg, char *env[], int exit_code)
// {
// 	ft_putstr_fd("bash: ", 2);
// 	ft_putstr_fd(arg, 2);
// 	ft_putstr_fd(": No such file or directory\n", 2);
// 	free_and_exit(cmds, env, exit_code);
// 	// exit(exit_code);
// }

void	handle_cmd_path_err(t_cmd *cmds, char *msg, char *env[], int exit_code)
{
	int	temp_errno;

	temp_errno = errno;
	if (temp_errno == EACCES)
		print_error(msg, "Permission denied");
	else if (temp_errno == ENOENT)
		print_error(msg, "command not found");
	else
		print_error(msg, strerror(temp_errno));
	ft_putstr_fd("\n", 2);
	free_and_exit(cmds, env, exit_code);
	// exit(exit_code);
}

void	print_error(char *str, char *msg)
{
	if (str)
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": ", 2);
	}
	if (msg)
		ft_putstr_fd(msg, 2);
}

void	handle_exec_error(t_cmd *cmds, char *path, char *env[] )
{
	int	exit_code;
	int	save_errno;

	save_errno = errno;
	// ft_free_triptr(&cmd_argvs);
	if (save_errno == EACCES)
	{
		exit_code = 126;
		print_error(path, "Permission denied");
	}
	else if (save_errno == ENOENT)
	{
		exit_code = 127;
		print_error(path, "No such file or directory");
	}
	else
	{
		exit_code = 1;
		print_error(path, strerror(save_errno));
	}
	free(path);
	free_and_exit(cmds, env, exit_code);
	// exit(exit_code);
}