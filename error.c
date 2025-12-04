#include "minishellD.h"

void	invalid_command(t_master **mstr, char *cmd)
{
	ft_putstr_fd (cmd, 2);
	ft_putstr_fd (": Command not found \n", 2);
	exit_minishell (mstr, 127);
}

void	invalid_path(char *cmd)
{
	ft_putstr_fd ("cd: ", 2);
	ft_putstr_fd (cmd, 2);
	ft_putstr_fd (": No such file or directory\n", 2);
}

void	no_perms_command(t_master **mstr, char *cmd)
{
	ft_putstr_fd (cmd, 2);
	ft_putstr_fd (": Permission denied\n", 2);
	exit_minishell (mstr, 126);
}

void	no_perms_path(char *cmd)
{
	ft_putstr_fd ("cd: ", 2);
	ft_putstr_fd (cmd, 2);
	ft_putstr_fd (": Permission denied\n", 2);
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
