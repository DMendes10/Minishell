
#include "minishellD.h"

int	executor(t_master *mstr, int cmd_count)
{
	t_cmdlist *ptr;

	mstr->data->pid = ft_calloc(cmd_count, sizeof(pid_t));
	mstr->data->last_fd = dup(0);
	ptr = mstr->cmd;
	while (ptr)
	{
		pipe_operator(ptr, mstr);
		ptr = ptr->next;
		mstr->data->i++;
	}
	mstr->exit = ft_wait (mstr->data->pid, cmd_count);
	// free(pid);
	close(mstr->data->last_fd);
	return (mstr->data->exit_code);
}

int	exec_built(t_cmdlist *cmd, t_master *mstr)
{
	if (ft_strncmp (cmd->command[0], "echo", 5) == 0)
		return(ft_echo(cmd->command, EXIT_CODE, ECHO_FLAG, ECHO_INDEX));
	else if (ft_strncmp (cmd->command[0], "exit", 5) == 0)
		return (ft_exit (cmd->command, mstr), 0);
	else if (ft_strncmp (cmd->command[0], "cd", 3) == 0)
		return (ft_cd(cmd->command, mstr));
	else if (ft_strncmp (cmd->command[0], "pwd", 4) == 0)
		return (ft_pwd());
	else if (ft_strncmp (cmd->command[0], "export", 7) == 0)
		return (ft_export(mstr, cmd));
	else if (ft_strncmp (cmd->command[0], "unset", 6) == 0)
		return (ft_unset(cmd->command, mstr));
	else if (ft_strncmp (cmd->command[0], "env", 4) == 0)
		return(ft_env(mstr->env));
	else
		return (1);
}

int	ft_wait(pid_t *proc_id, int cmd_count)
{
	int	status;
	int	exit_code;
	int i;

	status = 0;
	i = 0;
	exit_code = 0;
	while (i < cmd_count)
	{
		if (i == cmd_count - 1)
		{
			waitpid(proc_id[i], &status, 0);
			if (WIFEXITED (status))
				exit_code = WEXITSTATUS (status);
		}
		else
			waitpid(proc_id[i], NULL, 0);
		i++;
	}
	return (exit_code);
}
