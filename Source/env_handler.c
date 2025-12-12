/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogo <diogo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 15:02:08 by diogo             #+#    #+#             */
/*   Updated: 2025/12/12 16:29:20 by diogo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	env_init(t_master *mstr, char **env)
{
	char	**new_env;

	new_env = NULL;
	if (!env[0])
	{
		new_env = custom_env_builder (mstr);
		env_populator (mstr, new_env);
		free_array (new_env);
	}
	else
	{
		env_populator (mstr, env);
		update_shlvl (mstr);
	}
}

void	update_shlvl(t_master *mstr)
{
	t_envlst	*ptr;
	int			lvl;
	char		*new_lvl;

	ptr = mstr->env;
	while (ptr)
	{
		if (!ft_strncmp(ptr->token, "SHLVL", 6))
		{
			lvl = ft_atoi(ptr->var);
			lvl++;
			free (ptr->var);
			new_lvl = ft_itoa(lvl);
			ptr->var = ft_strdup(new_lvl);
			free (new_lvl);
			return ;
		}
		ptr = ptr->next;
	}
}

char	**custom_env_builder(t_master *mstr)
{
	char	str[PATH_MAX];
	char	*pwd;
	char	**new_env;

	pwd = getcwd(str, PATH_MAX);
	new_env = malloc (4 * sizeof(char *));
	if (!new_env)
		alloc_error (&mstr);
	new_env[0] = ft_strjoin ("PWD=", pwd);
	if (!new_env[0])
		alloc_error_exit (mstr, new_env);
	new_env[1] = ft_strdup ("SHLVL=1");
	if (!new_env[1])
		alloc_error_exit (mstr, new_env);
	new_env[2] = ft_strdup ("_=./minishell");
	if (!new_env[2])
		alloc_error_exit (mstr, new_env);
	new_env[3] = NULL;
	return (new_env);
}
