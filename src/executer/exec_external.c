
#include "minishell.h"

static	char	*check_cmd_only(t_cmd *cmds, char *arg, char *env[]);
// static	int		check_path_envp(char **envp);
// static	char	*get_path(char **envp, char *cmd);
// static	char	*find_path_envp(char **envp);
// static	char	*check_execution(char **path_parts, char *cmd);

void	exec_external(t_cmd *cmds, char **args, char *env[])
{	
	char	*path;
	struct stat	st;

	path = check_cmd_only(cmds, args[0], env);
	// printf("Before Path: %s\n", path);
	if (!path)
	{
		// if (access(args))
		// printf("path is no command\n");
		path = correct_path(args[0], env);
	}
	// printf("After Path: %s\n", path);
	if (path != NULL)
	{
		free(args[0]);
		args[0] = path;
	}
	else
		handle_cmd_error(cmds, args[0], env, 127);
	if (lstat(args[0], &st) == 0 && S_ISDIR(st.st_mode))
	{
		fprintf(stderr, "%s: Is a directory\n", args[0]);
		free_and_exit(cmds, env, 126);
	}
	execve(args[0], args, env);
	if (errno == ENOENT)
	{
		if (!path_exists(env))
			error_string(args[0]);
		else
			failed_exec(args[0]);
	}
	else
	{
		error_string(args[0]);
		free_and_exit(cmds, env, 126);
		// exit(126);
	}
	// path = check_cmd_only(cmds, args[0], env);
	// if (path)
	// {
	// 	if (check_path_envp(env) == 0)
	// 		handle_envp_error(cmds, args[0], env, 127);
	// 	path = get_path(env, args[0]);
	// 	if (!path)
	// 	{
	// 		print_error(args[0], NULL);
	// 		// ft_free_triptr(&cmd_argvs);
	// 		handle_cmd_path_err(cmds, NULL, env, 127);
	// 	}
	// }
	// execve(path, args, env);
	// handle_exec_error(cmds, path, env);
}

static	char	*check_cmd_only(t_cmd *cmds, char *arg, char *env[])
{
	char	*out;

	if (!arg || !cmds)
		return (NULL);
	if (arg[0] == '/' || (arg[0] == '.' && arg[1] == '/'))
	{
		if (access(arg, X_OK) == 0)
		{
			out = ft_strdup(arg);
			if (!out)
				return (NULL);
			return (out);
		}
		else if (access(arg, F_OK) == 0)
		{
			out = ft_strdup(arg);
			if (!out)
				return (NULL);
			return (out);
		}
		handle_no_file(cmds, arg, env, 127);
	}
	return (NULL);
}

// static	int	check_path_envp(char **envp)
// {
// 	int	out;
// 	int	i;

// 	if (!envp)
// 		return (0);
// 	i = 0;
// 	out = 0;
// 	while (envp[i])
// 	{
// 		if (ft_strnstr(envp[i], "PATH=", 5) != NULL)
// 		{
// 			out = 1;
// 			break ;
// 		}
// 		i++;
// 	}
// 	return (out);
// }

// static	char	*get_path(char **envp, char *cmd)
// {
// 	char	*out;
// 	char	*path_envp;
// 	char	**path_parts;

// 	path_envp = find_path_envp(envp);
// 	if (!path_envp)
// 		return (NULL);
// 	path_parts = ft_split(path_envp, ':');
// 	free(path_envp);
// 	if (!path_parts)
// 		return (NULL);
// 	out = check_execution(path_parts, cmd);
// 	ft_free_triptr(&path_parts);
// 	return (out);
// }

// static	char	*find_path_envp(char **envp)
// {
// 	char	*out;
// 	int		i;

// 	if (!envp)
// 		return (NULL);
// 	i = 0;
// 	while (envp[i])
// 	{
// 		if (ft_strnstr(envp[i], "PATH=", 5) != NULL)
// 		{
// 			out = ft_strdup(envp[i] + 5);
// 			if (out && out[0] == '\0')
// 			{
// 				free(out);
// 				return (NULL);
// 			}
// 			return (out);
// 		}
// 		i++;
// 	}
// 	return (NULL);
// }

// static	char	*check_execution(char **path_parts, char *cmd)
// {
// 	int		i;
// 	char	*temp_path;
// 	char	*out_path;

// 	i = 0;
// 	if (!cmd)
// 		return (NULL);
// 	while (path_parts[i])
// 	{
// 		temp_path = ft_strjoin(path_parts[i], "/");
// 		if (!temp_path)
// 			return (NULL);
// 		out_path = ft_strjoin(temp_path, cmd);
// 		free(temp_path);
// 		if (!out_path)
// 			return (NULL);
// 		if (access(out_path, X_OK) == 0)
// 			return (out_path);
// 		free(out_path);
// 		i++;
// 	}
// 	return (NULL);
// }