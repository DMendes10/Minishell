
#include "minishellD.h"

int	executor(t_master *mstr, int cmd_count)
{
	pid_t pid[cmd_count];
	t_cmdlist *ptr;

	mstr->data->last_fd = dup(STDIN_FILENO);
	ptr = mstr->cmd;
	while (ptr)
	{
		pipe_operator(ptr , mstr->data, pid);
		ptr = ptr->next;
		mstr->data->i++;
	}
	mstr->exit = ft_wait (pid);
	close(mstr->data->last_fd);
	return (mstr->data->exit_code);
}

int	exec_built(t_cmdlist *cmd, t_master *mstr)
{
	if (ft_strncmp (cmd->command[0], "echo", 6) == 0)
		return(ft_echo(cmd->command, EXIT_CODE, ECHO_FLAG, ECHO_INDEX));
	else if (ft_strncmp (cmd->command[0], "exit", 5) == 0)
		return (ft_exit (cmd->command, mstr), 0);
	else if (ft_strncmp (cmd->command[0], "cd", 3) == 0)
		return (ft_cd(cmd->command, mstr));
	else if (ft_strncmp (cmd->command[0], "pwd", 4) == 0)
		return (ft_pwd());
	else if (ft_strncmp (cmd->command[0], "export", 7) == 0)
		ft_export(mstr, cmd->command[0]);
	else if (ft_strncmp (cmd->command[0], "unset", 6) == 0)
		ft_unset(cmd->command, mstr);
	else if (ft_strncmp (cmd->command[0], "env", 4) == 0)
		return(ft_env(mstr->env));
	else
		return (1);
}

int	ft_wait(pid_t *proc_id)
{
	int	status;
	int	exit_code;

	exit_code = 0;
	waitpid(proc_id[1], &status, 0);
	if (WIFEXITED (status))
		exit_code = WEXITSTATUS (status);
	waitpid(proc_id[0], NULL, 0);
	return (exit_code);
}
