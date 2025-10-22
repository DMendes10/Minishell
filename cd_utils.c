#include "minishellD.h"

int chdir_env_pwd(t_envlst *lst, char *directory)
{
	t_envlst *ptr;
	int exit_code;

	ptr = lst;
	while (ptr)
	{
		if (!ft_strncmp(ptr->token, "OLDPWD", 7))
		{	
			free (ptr->var);
			ptr->var = ft_strdup(getcwd(NULL, 0));
		}
		ptr = ptr->next;
	}
	exit_code = chdir(directory);
	ptr = lst;
	while (ptr)
	{
		if (!ft_strncmp(ptr->token, "PWD", 4))
		{	
			free (ptr->var);
			ptr->var = ft_strdup(getcwd(NULL, 0));
		}
		ptr = ptr->next;
	}
	return(exit_code);
}

int find_home(t_envlst *lst)
{
	t_envlst *ptr;

	ptr = lst;
	while (ptr)
	{
		if (!ft_strncmp(ptr->token, "HOME", 5))
			return(chdir_env_pwd(lst, ptr->var));
		ptr = ptr->next;
	}
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
