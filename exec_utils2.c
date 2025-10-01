
#include "minishell.h"

void	child_process( int last_fd, int fdin, int fdout, int pipefd[], t_cmdlist *ptr)
{
	char *path;

	if (dup2(last_fd, STDIN_FILENO) == -1)
		return_error();
	close (last_fd);
	if (ptr->input)
		input_redirect (ptr->input, fdin);
	if (ptr->next)
	{
		if (dup2(pipefd[1], STDOUT_FILENO))
			return_error();
		close (pipefd[0]);
		close (pipefd[1]);
	}
	else if (ptr->output)
		output_redirect (ptr->output, fdout);
	path = getenv("PATH");
	if (execve (path, ptr->command, env) == -1)
		return_error();
}

void	input_redirect (char *input, int fdin)
{
	fdin = open(input, O_RDONLY);
	if (fdin == -1)
		return_error();
	if (dup2 (fdin, STDIN_FILENO) == -1)
		return_error();
	close (fdin);
}

void	output_redirect (char *output, int fdout)
{
	fdout = open (output, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fdout == -1)
		return_error();
	if (dup2 (fdout, STDOUT_FILENO) == -1)
		return_error();
	close (fdout);
}

void	exec_init (t_edata *data)
{
	data = malloc (sizeof(t_data));
	data = ft_memset (data, 0, sizeof (t_data));
	
}