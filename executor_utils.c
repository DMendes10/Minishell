
#include "minishellD.h"

int	executor (char **env, t_cmdlist *commands, int cmd_count)
{
	pid_t pid[cmd_count];
	t_edata	*data;

	exec_init (data);
	data->last_fd = dup(STDIN_FILENO);
	if (data->last_fd == -1)
		return_error();
	data->ptr = commands;
	while (data->ptr)
	{
		io_operator(data, pid);
		data->ptr = data->ptr->next;
		data->i++;
	}
	data->exit_code = ft_wait (pid);
	close(data->last_fd);
	return (data->exit_code);
}

int exec_built (t_cmdlist *cmdlst, t_envlst *envlst)
{
	if (ft_strncmp (cmdlst->command[0], "echo", 5) == 0)
            return(ft_echo(cmdlst->command));
        else if (ft_strncmp (cmdlst->command[0], "exit", 5) == 0)
            exit (0);
        else if (ft_strncmp (cmdlst->command[0], "cd", 3) == 0)
            return (ft_cd(cmdlst->command));
        else if (ft_strncmp (cmdlst->command[0], "pwd", 4) == 0)
            return (ft_pwd());
        // else if (ft_strncmp (command[0], "export", 100) == 0)
        //     ft_export();
        // else if (ft_strncmp (command[0], "unset", 100) == 0)
        //     ft_unset();
        else if (ft_strncmp (cmdlst->command[0], "env", 4) == 0)
            return(ft_env(envlst));
		else
			return (-1);
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
