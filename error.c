
#include "minishellD.h"

void	return_error(char *error)
{
	perror (error);
	exit(1);
}

// void	close_files(int *fd, int file)
// {
// 	if (close(fd[0]) < 0 || close(fd[1]) < 0)
// 		return_error("closing error");
// 	if (close(file) < 0)
// 		return_error("closing error");
// }

void	invalid_command(char **array, char *cmd)
{
	ft_putstr_fd (cmd, 2);
	ft_putstr_fd (": Command not found \n", 2);
	free_array (array);
	// exit (127);
}

void	invalid_path(char **array, char *cmd)
{
	ft_putstr_fd ("cd: ", 2);
	ft_putstr_fd (cmd, 2);
	ft_putstr_fd (": No such file or directory\n", 2);
	free_array (array);
	// exit (1);
	return;
}


void	no_perms_command(char **array, char *cmd)
{
	ft_putstr_fd ("cd: ", 2);
	ft_putstr_fd (cmd, 2);
	ft_putstr_fd (": Permission denied\n", 2);
	free_array (array);
	// exit (1);
	return ;
}

void	no_perms_path(char **array, char *cmd)
{
	ft_putstr_fd (cmd, 2);
	ft_putstr_fd (": Permission denied \n", 2);
	free_array (array);
	exit (126);
}

void	free_array(char **s)
{
	size_t	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		free (s[i]);
		i++;
	}
	free (s);
}


