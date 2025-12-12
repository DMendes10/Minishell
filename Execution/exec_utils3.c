/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogo <diogo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 15:02:38 by diogo             #+#    #+#             */
/*   Updated: 2025/12/12 16:29:20 by diogo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	redir_expansion(t_master *mstr, char **redir, int i)
{
	int	j;

	j = 0;
	if (ft_count_words (redir[i], ' ') == 1)
	{
		if (ft_strchr (redir[i], '$'))
		{
			while (redir[i][j])
			{
				if (redir_expand_helper(mstr, redir, i, j))
					return (1);
				j++;
			}
		}
	}
	expand_redir (mstr, redir);
	return (0);
}

int	redir_expand_helper(t_master *mstr, char **redir, int i, int j)
{
	char	*tmp;
	char	*key;

	tmp = NULL;
	key = NULL;
	if (redir[i][j] == '$')
	{
		key = get_varkey (&redir[i][j]);
		if (*env_finder (mstr->env, key))
		{
			tmp = env_finder (mstr->env, key);
			if (ft_count_words (tmp, ' ') > 1)
				return (sign()->exit_code = 1, free (key), 1);
			free (key);
		}
		else
		{
			free (key);
			key = get_varkey(&redir[i][j + 1]);
			if (!key)
				return (sign()->exit_code = 1, 1);
		}
	}
	return (0);
}

void	expand_redir(t_master *mstr, char **redir)
{
	int		i;
	char	*key;

	i = 0;
	key = NULL;
	while (redir[i])
	{
		key = get_varkey(redir[i]);
		while (key)
		{
			if (check_exp(&redir[i], &key, mstr))
			{
				search_and_replace(&redir[i], key, mstr);
			}
			key = get_varkey(redir[i]);
		}
		i++;
	}
}

void	path_checker(t_master **mstr, char *path, t_cmdlist *cmd, int i)
{
	if (!path)
		invalid_command (mstr, cmd->command[0]);
	if (access (path, F_OK) != 0)
		invalid_command (mstr, cmd->command[0]);
	if (access (path, X_OK) != 0)
		no_perms_command (mstr, cmd->command[0]);
	if (path[0] == '.' && !path[1])
	{
		ft_putstr_fd (cmd->command[0], 2);
		ft_putstr_fd (": filename argument required\n", 2);
		ft_putstr_fd (cmd->command[0], 2);
		ft_putstr_fd (": usage: . filename [arguments]\n", 2);
		exit_minishell (mstr, 2);
	}
	if (path[0] == '.' && path[1] == '.')
		invalid_command (mstr, cmd->command[0]);
	while (path[i] == '.' || path[i] == '/')
		i++;
	if (!path[i])
	{
		ft_putstr_fd (cmd->command[0], 2);
		ft_putstr_fd (": Is a directory\n", 2);
		exit_minishell (mstr, 126);
	}
}
