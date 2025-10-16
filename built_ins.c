
#include "minishellD.h"

int ft_cd(char **command)
{
	char *h_env;

	if (!command [1])
	{
		h_env = getenv ("HOME");
		if (!h_env)
			return(ft_putstr_fd ("cd: HOME not set\n", 2), 1);
		chdir (h_env);
	}
	else if (!command[2])
	{
		if (access (command[1], F_OK) != 0)
			invalid_command (command, command[1]);
		if (access (command[1], X_OK) != 0)
			no_perms_command (command, command[1]);
		else
			chdir (command[1]);
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
	return (exit_code);
}

int ft_echo (char **command)
{
	int exit_code;
	int i;
	char *line;
		
	line = NULL;
	i = 1;
	exit_code = 0;
	if (command[1] && ft_strncmp (command[1], "-n", 100) == 0)
		i = 2;
	while (command[i])
	{
		line = ft_strjoin_gnl (line, command[i]);
		i++;
		if (command[i])
			line = ft_strjoin_gnl (line, " ");
	}
	if (command[1] && ft_strncmp (command[1], "-n", 100) == 0)
		printf ("%s",line);
	else
		printf ("%s\n", line);
	return (exit_code);
}

int	export(t_envlst *lst, t_cmdlist *cmdlst)
{
	int i;
	int exit_code;
	int super_exit;

	i = 1;
	exit_code = 0;
	super_exit = 0;
	if (!cmdlst->command[1])
		return (simple_export(lst));
	else
	{
		while (cmdlst->command[i])
		{
			if (cmdlst->command[i][0] == '=')
			{
				printf("export: `%s': not a valid identifier\n", cmdlst->command[i]);
				super_exit = 1;
				i++;
			}
			
		}
	}
	
}

int	ft_envlst_size(t_envlst *lst)
{
	int	i;
	t_envlst *ptr;

	i = 0;
	ptr = lst;
	if (!ptr)
		return (0);
	while (!ptr)
	{
		ptr = ptr->next;
		i++;
	}
	return (i);
}
