
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
			return (free_master(&mstr));
	}
	if (cmd->next)
	{
		dup2(mstr->data->pipefd[1], STDOUT_FILENO);
		close (mstr->data->pipefd[0]);
		close (mstr->data->pipefd[1]);
	}
	if (cmd->output)
		output_redirect (mstr, cmd);
	if (exec_built (cmd, mstr))
		return (mstr->exit);
	paths = ft_split (env_finder(cmd, "PATH"), ':');
	path = path_finder(cmd->command, paths);
	path_checker(path, mstr);
	free_array (paths);
	env = envlst_to_char (mstr);
	if (execve (path, cmd->command, env) == -1)
		return_error();
}

int	input_redirect (t_master *mstr, t_cmdlist *cmd)
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
				printf("%s", cmd->input[i + 1]);
				perror(":");
				return (1);
			}
			dup2 (mstr->data->fdin, STDIN_FILENO);
		}
		i++;
		close (mstr->data->fdin);
	}
	return (0);
}

void	output_redirect (t_master *mstr, t_cmdlist *cmd)
{
	int	i;

	i = 0;
	while (cmd->output[i])
	{
		if (!ft_strncmp (cmd->output[i], ">", 1))
		{
			mstr->data->fdout = open (cmd->output[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (mstr->data->fdout == -1)
				return_error();
			if (dup2 (mstr->data->fdout, STDOUT_FILENO) == -1)
				return_error();
			i += 2;
		}
		else
		{
			mstr->data->fdout = open (cmd->output[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (mstr->data->fdout == -1)
				return_error();
			if (dup2 (mstr->data->fdout, STDOUT_FILENO) == -1)
				return_error();
			i += 2;
		}
		close (mstr->data->fdout);
	}
}

void	exec_init (t_edata *data)
{
	data = malloc (sizeof(t_edata));
	data = ft_memset (data, 0, sizeof (t_edata));
}

void	pipe_operator(t_cmdlist *cmd, t_master *mstr, pid_t pid[])
{
	if (cmd->next)
		{
			if (pipe (mstr->data->pipefd) == -1)
				return_error();
		}
		pid[mstr->data->i] = fork();
		if (pid[mstr->data->i] == 0)
			child_process (mstr, cmd);
		close (mstr->data->last_fd);
		if (cmd->next)
		{
			close (mstr->data->pipefd[1]);
			mstr->data->last_fd = mstr->data->pipefd[0];
		}
}
