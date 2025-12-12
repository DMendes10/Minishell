/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogo <diogo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 15:25:39 by jomaia            #+#    #+#             */
/*   Updated: 2025/12/12 16:38:52 by diogo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_exp(char **s, char **key, t_master *master)
{
	char	*var;
	int		i;

	i = 0;
	var = NULL;
	if (!ft_strncmp(*key, "?", 2))
		var = ft_itoa(master->exit);
	else
		var = env_finder(master->env, *key);
	if (var)
	{
		if (!ft_strncmp(*key, "?", 2))
			free (var);
		return (1);
	}
	else
	{
		while ((*s)[i] && (*s)[i] != '$')
			i++;
		if ((*s)[i] && (*s)[i] == '$')
			(*s)[i] = -1;
		free (*key);
		return (0);
	}
}

void	restore_cmd(t_cmdlist *node)
{
	int			i;
	int			j;
	int			quotes;

	i = 0;
	j = 0;
	quotes = 0;
	while (node->command[i])
	{
		j = 0;
		while (node->command[i][j])
		{
			if (node->command[i][j] == -1 && quotes)
				node->command[i][j] = '$';
			else if (node->command[i][j] == '\'' || node->command[i][j] == '\"')
				quotes = quotes_check(node->command[i][j], quotes);
			j++;
		}
		i++;
	}
}
