
#include "minishell.h"

int	executor (char **env, t_cmdlist *commands)
{
	pid_t pid[commands->cmd_count];
	t_edata	*data;

	exec_init (data)
	i = 0;
	last_fd = dup(STDIN_FILENO);
	if (last_fd == -1)
		return_error();
	ptr = commands;
	while (ptr)
	{
		if (ptr->next)
		{
			if (pipe (pipefd) == -1)
				return_error();
		}
		pid[i] = fork();
		if (pid[i] == -1)
			return_error();
		if (pid == 0)
			child_process ();
		close (last_fd);
		if (ptr->next)
		{
			close (pipefd[1]);
			last_fd = pipefd[0];
		}
		ptr = ptr->next;
		i++;
	}
	exit_code = ft_wait (pid);
	close(last_fd);
	return (exit_code);
}

int exec_built (t_cmds *cmdlst, char **env)
{
	if (ft_strncmp (command[0], "echo", 100) == 0)
            return(ft_echo(command));
        else if (ft_strncmp (command[0], "exit", 100) == 0)
            exit (0);
        else if (ft_strncmp (command[0], "cd", 100) == 0)
            ft_cd(command);
        else if (ft_strncmp (command[0], "pwd", 100) == 0)
            ft_pwd();
        // else if (ft_strncmp (command[0], "export", 100) == 0)
        //     ft_export();
        // else if (ft_strncmp (command[0], "unset", 100) == 0)
        //     ft_unset();
        else if (ft_strncmp (command[0], "env", 100) == 0)
            ft_env(env);
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
