/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogo <diogo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 15:02:03 by diogo             #+#    #+#             */
/*   Updated: 2025/12/09 15:02:04 by diogo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishellD.h"

void	chdir_env_pwd(t_master *mstr, char *directory)
{
	t_envlst	*ptr;
	char		str[PATH_MAX];

	ptr = mstr->env;
	while (ptr)
	{
		if (!ft_strncmp(ptr->token, "OLDPWD", 7))
		{
			free (ptr->var);
			ptr->var = ft_strdup(env_finder(mstr->env, "PWD"));
			if (!ptr->var)
				alloc_error (&mstr);
			break ;
		}
		ptr = ptr->next;
	}
	if (!ptr)
		reset_oldpwd(mstr);
	sign()->exit_code = chdir(directory);
	if (!getcwd(str, PATH_MAX))
		printf ("cd: error retrieving current directory: getcwd:\
			 cannot access parent directories: No such file or directory\n");
	update_pwd (mstr);
}

void	reset_oldpwd(t_master *mstr)
{
	char	str[PATH_MAX];
	char	*old;

	old = NULL;
	if (getcwd (str, PATH_MAX))
		old = ft_strjoin ("OLDPWD=", getcwd (str, PATH_MAX));
	else
		old = ft_strdup ("OLDPWD=");
	exp_full (mstr, old);
	free (old);
}

void	update_pwd(t_master *mstr)
{
	t_envlst	*ptr;
	char		str[PATH_MAX];
	char		*pwd;

	pwd = NULL;
	ptr = mstr->env;
	while (ptr)
	{
		if (!ft_strncmp(ptr->token, "PWD", 4))
		{
			free (ptr->var);
			ptr->var = ft_strdup(getcwd(str, PATH_MAX));
			if (!ptr->var)
				alloc_error(&mstr);
			return ;
		}
		ptr = ptr->next;
	}
	if (getcwd (str, PATH_MAX))
		pwd = ft_strjoin ("PWD=", getcwd (str, PATH_MAX));
	else
		pwd = ft_strdup ("PWD=");
	exp_full (mstr, pwd);
	free (pwd);
}

int	find_home(t_master *mstr)
{
	t_envlst	*ptr;

	ptr = mstr->env;
	while (ptr)
	{
		if (!ft_strncmp(ptr->token, "HOME", 5))
			return (sign()->exit_code = 0, chdir_env_pwd(mstr, ptr->var), 0);
		ptr = ptr->next;
	}
	sign()->exit_code = 1;
	return (ft_putstr_fd ("cd: HOME not set\n", 2), 1);
}

int	valid_flag(char *flag)
{
	int	i;

	i = 0;
	if (flag[i] != '-')
		return (1);
	i++;
	while (flag[i])
	{
		if (flag[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}
