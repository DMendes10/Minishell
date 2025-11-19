#include "minishellD.h"

void chdir_env_pwd(t_master *mstr, char *directory)
{
	t_envlst *ptr;
	char str[PATH_MAX];

	ptr = mstr->env;
	while (ptr)
	{
		if (!ft_strncmp(ptr->token, "OLDPWD", 7))
		{	
			free (ptr->var);
			ptr->var = ft_strdup(env_finder(mstr->env, "PWD"));
			if (!ptr->var)
				alloc_error (&mstr);
		}
		ptr = ptr->next;
	}
	mstr->exit = chdir(directory);
	if (!getcwd(str, PATH_MAX))
		printf ("cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n");
	update_pwd (mstr);
}

void	update_pwd(t_master *mstr)
{
	t_envlst *ptr;
	char str[PATH_MAX];

	ptr = mstr->env;
	while (ptr)
	{
		if (!ft_strncmp(ptr->token, "PWD", 4))
		{	
			free (ptr->var);
			ptr->var = ft_strdup(getcwd(str, PATH_MAX));
			if (!ptr->var)
				alloc_error(&mstr);
		}
		ptr = ptr->next;
	}
}

int find_home(t_master *mstr)
{
	t_envlst *ptr;

	ptr = mstr->env;
	while (ptr)
	{
		if (!ft_strncmp(ptr->token, "HOME", 5))
			return(mstr->exit = 0, chdir_env_pwd(mstr, ptr->var), 0);
		ptr = ptr->next;
	}
	mstr->exit = 1;
	return(ft_putstr_fd ("cd: HOME not set\n", 2), 1);
}

int valid_flag(char *flag)
{
	int i;

	i = 1;
	while (flag[i])
	{
		if (flag[i] != 'n')
			return (1);
		i++;
	}
	return(0);
}
