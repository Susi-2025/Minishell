
#include "minishell.h"

static	void	simple_cmd_print(t_simple_cmd *simple_cmd);

void	cmd_print(t_cmd *cmds)
{
	printf("Value of cmds_capacity: %d\n", cmds->cmds_capacity);
	printf("Value of cmds_count: %d\n", cmds->cmds_count);
	printf("Value of out_file: %s\n", cmds->out_file);
	printf("Value of in_file: %s\n", cmds->in_file);
	printf("Value of err_file: %s\n", cmds->err_file);
	printf("Value of here_doc: %s\n", cmds->here_doc);
	printf("Value of file_append: %s\n", cmds->file_append);
	simple_cmd_print(cmds->simple_cmds);
}

static	void	simple_cmd_print(t_simple_cmd *simple_cmd)
{
	int	i;
	printf("Value of args_capacity: %d\n", simple_cmd->args_capacity);
	printf("Value of args_count: %d\n", simple_cmd->args_count);
	i = 0;
	while (simple_cmd->args[i])
	{
		printf("Value of args at %d position is: %s\n", i, simple_cmd->args);
		i++;
	}
}