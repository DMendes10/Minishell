
#include "minishellD.h"

int ft_cd(char **command, t_envlst *lst)
{
	char *h_env;

	if (!command [1])
		return(find_home(lst));
	else if (!command[2])
	{
		if (access (command[1], F_OK) != 0)
			invalid_command (command, command[1]);
		if (access (command[1], X_OK) != 0)
			no_perms_command (command, command[1]);
		else
			chdir_env_pwd(lst, command[1]);
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
		if (ptr->var && ptr->var[0])
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
	return (exit_code);
}

int ft_echo (char **command, int exit_code, int flag, int i)
{
	char *line;
		
	line = NULL;
	if (command[i] && ft_strncmp (command[i], "-n", 2))
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
		if (command[i++])
			line = ft_strjoin_gnl (line, " ");
	}
	if (line)
	{
		printf ("%s",line);
		free (line);
	}
	if (!flag)
		printf ("\n");
	return (exit_code);
}

int	export(t_envlst *lst, t_cmdlist *cmdlst)
{
	if (!cmdlst->command[1])
		return (simple_export(lst));
	else
		return (add_export(lst, cmdlst, EXIT_CODE, SUPER_EXIT));
}

