
#include "minishellD.h"

int ft_cd(char **command, t_master *mstr)
{
	// char *h_env;

	if (!command [1])
		return(find_home(mstr));
	else if (!command[2])
	{
		if (access (command[1], F_OK) != 0)
			invalid_path(command, command[1]);
		if (access (command[1], X_OK) != 0)
			no_perms_path (command, command[1]);
		else
			chdir_env_pwd(mstr, command[1]);
	}
	else
		return(ft_putstr_fd ("cd: too many arguments\n", 2), 1);
	return (0);
}

int ft_env(t_envlst *list)
{
	t_envlst *ptr;

	ptr = list;
	while (ptr)
	{
		if (ptr->var)
			printf ("%s=%s\n", ptr->token, ptr->var);
		ptr = ptr->next;
	}
	return (0);
}

int ft_pwd()
{
	int exit_code;
	char *path;

	path = NULL;
	exit_code = 0;
	path = getcwd(NULL, 0);
	if (!path)
		printf ("%s\n", getenv ("PWD"));
	else
		printf ("%s\n", path);
	free (path);
	return (0);
}

int ft_echo (char **command, int exit_code, int flag, int i)
{
	char *line;
	(void)exit_code;
		
	line = NULL;
	if (command[i] && !ft_strncmp (command[i], "-n", 2))
	{
		while (!valid_flag(command[i]))
		{
			flag++;
			i++;
		}
	}
	while (command[i])
	{
		line = ft_strjoin_gnl (line, command[i]);
		if (command[1 + i++])
			line = ft_strjoin_gnl (line, " ");
	}
	if (line)
	{
		printf ("%s",line);
		free (line);
	}
	if (!flag)
		printf ("\n");
	return (0);
}

int	ft_export(t_master *mstr, t_cmdlist *cmdlst)
{
	if (!cmdlst->command[1])
		return (simple_export(mstr));
	else
		return (add_export(mstr, cmdlst, EXIT_CODE, SUPER_EXIT));
}

