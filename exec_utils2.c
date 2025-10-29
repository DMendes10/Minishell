
#include "minishellD.h"

void	child_process(t_edata *data)
{
	char **paths;
	char *path;

	if (dup2(data->last_fd, STDIN_FILENO) == -1)
		return_error();
	close (data->last_fd);
	if (data->ptr->input)
		input_redirect (data);
	if (data->ptr->next)
	{
		if (dup2(data->pipefd[1], STDOUT_FILENO))
			return_error();
		close (data->pipefd[0]);
		close (data->pipefd[1]);
	}
	if (data->ptr->output)
		output_redirect (data->ptr->output, data->fdout);
	paths = ft_split (getenv("PATH"), ':');
	path = path_finder(data->ptr->command, paths);
	path_checker(path, data);
	free_array (paths);
	if (execve (path, data->ptr->command, env) == -1)
		return_error();
}

void	input_redirect (t_edata *data)
{
	int i;

	i = 0;
	while (data->ptr->input[i])
	{
		if (!ft_strncmp (data->ptr->input[i], "<", 1))
		{
			data->fdin = open(data->ptr->input[i + 1], O_RDONLY);
			if (data->fdin == -1)
				return_error();
			if (dup2 (data->fdin, STDIN_FILENO) == -1)
				return_error();
			i += 2;
		}
		else
		{
			hdoc_rdwr(data->ptr->input[i + 1]);
			data->fdin = open("tmp_heredoc.txt", O_RDONLY);
			if (data->fdin == -1)
				return_error();
			if (dup2 (data->fdin, STDIN_FILENO) == -1)
				return_error();
			unlink ("tmp_heredoc.txt");
			i += 2;
		}
		close (data->fdin);
	}
}

void	output_redirect (t_edata *data)
{
	int	i;

	i = 0;
	while (data->ptr->output[i])
	{
		if (!ft_strncmp (data->ptr->output[i], ">", 1))
		{
			data->fdout = open (data->ptr->output[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (data->fdout == -1)
				return_error();
			if (dup2 (data->fdout, STDOUT_FILENO) == -1)
				return_error();
			i += 2;
		}
		else
		{
			data->fdout = open (data->ptr->output[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (data->fdout == -1)
				return_error();
			if (dup2 (data->fdout, STDOUT_FILENO) == -1)
				return_error();
			i += 2;
		}
		close (data->fdout);
	}
}

void	exec_init (t_edata *data)
{
	data = malloc (sizeof(t_edata));
	data = ft_memset (data, 0, sizeof (t_edata));
}

void	pipe_operator(t_edata *data, pid_t pid[])
{
	if (data->ptr->next)
		{
			if (pipe (data->pipefd) == -1)
				return_error();
		}
		pid[data->i] = fork();
		if (pid[data->i] == 0)
			child_process (data);
		close (data->last_fd);
		if (data->ptr->next)
		{
			close (data->pipefd[1]);
			data->last_fd = data->pipefd[0];
		}
}
