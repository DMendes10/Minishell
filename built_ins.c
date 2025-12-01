
#include "minishellD.h"

int ft_cd(char **command, t_master *mstr)
{
	if (!command [1])
		return(find_home(mstr));
	else if (!command[2])
	{
		if (access (command[1], F_OK) != 0)
			return (mstr->exit = 1, invalid_path(command[1]), 0);
		else if (access (command[1], X_OK) != 0)
			return(mstr->exit = 1, no_perms_path (command[1]), 0);
		else
			chdir_env_pwd(mstr, command[1]);
	}
	else
	{
		mstr->exit = 1;
		return(ft_putstr_fd ("cd: too many arguments\n", 2), 1);
	}
	return (0);
}

int ft_env(t_master *mstr, t_envlst *list)
{
	t_envlst *ptr;

	ptr = list;
	while (ptr)
	{
		if (ptr->var)
			printf ("%s=%s\n", ptr->token, ptr->var);
		ptr = ptr->next;
	}
	mstr->exit = 0;
	return (0);
}

int ft_pwd(t_master *mstr)
{
	char *path;
	char str[PATH_MAX];

	path = NULL;
	
	if (!getcwd(str, PATH_MAX) && ft_strlen(env_finder(mstr->env, "PWD")) == 0)
	{
		path = ft_strjoin (env_finder(mstr->env, "OLDPWD"), "/..");
		printf ("%s\n", path);
		free (path);
	}
	else if (!env_finder (mstr->env, "PWD"))
	{
		path = getcwd(str, PATH_MAX);
		printf ("%s\n", path);
	}
	else
	{
		path = ft_strdup (env_finder(mstr->env, "PWD"));
		printf ("%s\n", path);
		free (path);
	}
	mstr->exit = 0;
	return (0);
}

int ft_echo(t_master *mstr, char **command, int flag, int i)
{
	char *line;
		
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
		if (command[1 + i++] && *line && command[1 + i++])
			line = ft_strjoin_gnl (line, " ");
	}
	if (line)
	{
		printf ("%s",line);
		free (line);
	}
	if (!flag)
		printf ("\n");
	return (mstr->exit = 0, 0);
}

int	ft_export(t_master *mstr, t_cmdlist *cmdlst)
{
	if (!cmdlst->command[1])
		return (simple_export(mstr));
	else
		return (add_export(mstr, cmdlst, SUPER_EXIT));
}

