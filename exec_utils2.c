
#include "minishellD.h"

void	child_process(t_master *mstr, t_cmdlist *cmd)
{
	char **paths;
	char **env;
	char *path;

	dup2(mstr->data->last_fd, STDIN_FILENO);
	close (mstr->data->last_fd);
	if (cmd->input)
	{
		if(input_redirect (mstr, cmd))
			exit_minishell(&mstr, 1);
	}
	if (cmd->next)
	{
		dup2(mstr->data->pipefd[1], STDOUT_FILENO);
		close (mstr->data->pipefd[0]);
		close (mstr->data->pipefd[1]);
	}
	if (cmd->output)
	{
		if(output_redirect (mstr, cmd))
			exit_minishell(&mstr, 1);
	}
	if (!exec_built (cmd, mstr))
		exit_minishell (&mstr, mstr->exit);
	paths = ft_split (env_finder(mstr->env, "PATH"), ':');
	path = path_finder(cmd->command, paths);
	path_checker(path, cmd);
	env = envlst_to_char (mstr);
	if (execve (path, cmd->command, env) == -1)
	{
		perror (cmd->command[0]);
		free_array(env);
		exit_minishell(&mstr, 127);
	}
}

void	built_in_single_exec(t_master *mstr, t_cmdlist *cmd)
{
	int saved_stdin;
	int saved_stdout;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	dup2(mstr->data->last_fd, STDIN_FILENO);
	close (mstr->data->last_fd);
	if (cmd->input)
	{
		if(input_redirect (mstr, cmd))
		{
			dup2(saved_stdin, STDIN_FILENO);
			dup2(saved_stdout, STDOUT_FILENO);
			close(saved_stdin);
			close(saved_stdout);
			return;
		}
	}
	if (cmd->output)
	{
		if (output_redirect (mstr, cmd))
		{
			dup2(saved_stdin, STDIN_FILENO);
			dup2(saved_stdout, STDOUT_FILENO);
			close(saved_stdin);
			close(saved_stdout);
			return;
		}
	}
	exec_built (cmd, mstr);
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
	// exit_minishell (&mstr, mstr->exit);
}

int	input_redirect(t_master *mstr, t_cmdlist *cmd)
{
	int i;

	i = 0;
	if (hdoc_handler (mstr, cmd))
		return (1);
	while (cmd->input[i])
	{
		if (!ft_strncmp (cmd->input[i], "<", 2))
		{
			mstr->data->fdin = open(cmd->input[i + 1], O_RDONLY);
			if (mstr->data->fdin < 0)
			{
				// printf("%s", cmd->input[i + 1]);
				// fflush (stdin);
				perror(cmd->input[i + 1]);
				return (1);
			}
			dup2 (mstr->data->fdin, STDIN_FILENO);
			close (mstr->data->fdin);
		}
		i++;
	}
	return (0);
}

int	output_redirect(t_master *mstr, t_cmdlist *cmd)
{
	int	i;

	i = 0;
	while (cmd->output[i])
	{
		if (!ft_strncmp (cmd->output[i], ">", 2))
		{
			mstr->data->fdout = open (cmd->output[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (mstr->data->fdout == -1)
			{
				printf("%s", cmd->output[i + 1]);
				perror(": ");
				return (1);
				// exit_minishell (&mstr, 1);
			}
			dup2 (mstr->data->fdout, STDOUT_FILENO);
			close (mstr->data->fdout);
		}
		else if (!ft_strncmp (cmd->output[i], ">>", 3))
		{
			mstr->data->fdout = open (cmd->output[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (mstr->data->fdout == -1)
			{
				printf("%s", cmd->output[i + 1]);
				perror(": ");
				return (1);
				// exit_minishell (&mstr, 1);
			}
			dup2 (mstr->data->fdout, STDOUT_FILENO);
			close (mstr->data->fdout);
		}
		i++;
		// close (mstr->data->fdout);
	}
	return (0);
}

void	exec_init(t_edata *data)
{
	data = malloc (sizeof(t_edata));
	data = ft_memset (data, 0, sizeof (t_edata));
}

void	pipe_operator(t_cmdlist *cmd, t_master *mstr)
{
	if (cmd->next)
	{
		if (pipe (mstr->data->pipefd) == -1)
		{
			perror("pipe: ");
			exit_minishell (&mstr, 1);
		}
	}
	if (is_built_in(cmd) && cmdlist_size(cmd) == 1)
	{
		built_in_single_exec(mstr, cmd);
		close (mstr->data->last_fd);
		return ;
	}
	mstr->data->pid[mstr->data->i] = fork();
	if (mstr->data->pid[mstr->data->i] == 0)
		child_process (mstr, cmd);
	close (mstr->data->last_fd);
	if (cmd->next)
	{
		close (mstr->data->pipefd[1]);
		mstr->data->last_fd = mstr->data->pipefd[0];
	}
}

int	is_built_in(t_cmdlist *cmd)
{
	if (ft_strncmp (cmd->command[0], "echo", 5) == 0)
		return(1);
	else if (ft_strncmp (cmd->command[0], "exit", 5) == 0)
		return (1);
	else if (ft_strncmp (cmd->command[0], "cd", 3) == 0)
		return (1);
	else if (ft_strncmp (cmd->command[0], "pwd", 4) == 0)
		return (1);
	else if (ft_strncmp (cmd->command[0], "export", 7) == 0)
		return (1);
	else if (ft_strncmp (cmd->command[0], "unset", 6) == 0)
		return (1);
	else if (ft_strncmp (cmd->command[0], "env", 4) == 0)
		return(1);
	else
		return (0);
}
