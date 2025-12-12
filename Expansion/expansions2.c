/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogo <diogo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 15:25:49 by jomaia            #+#    #+#             */
/*   Updated: 2025/12/12 16:38:42 by diogo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	hdoc_del_prep(t_master *mstr)
{
	t_cmdlist	*node;
	int			i;
	int			j;

	i = 0;
	j = 0;
	node = mstr->cmd;
	while (node)
	{
		while (node->input && node->input[i])
		{
			j = 0;
			if (ft_strchr(node->input[i], '$'))
				dollar_search (mstr, i, j);
			i++;
		}
		i = 0;
		node = node->next;
	}
}

void	dollar_search(t_master *mstr, int i, int j)
{
	t_cmdlist	*node;

	node = mstr->cmd;
	while (node->input[i][j])
	{
		if (node->input[i][j] == '$')
		{
			if (!ft_strncmp(node->input[i - 1], "<<", 2))
			{
				if (node->input[i][j + 1] && (node->input[i][j + 1] == '\'' \
|| node->input[i][j + 1] == '\"'))
					remove_dollar (&node->input[i]);
			}
		}
		j++;
	}
}

void	remove_dollar(char **input)
{
	int		i;
	char	*tmp;
	char	*tmp2;
	char	*new;

	i = 0;
	i = ft_strchar_int (*input, '$');
	tmp = ft_substr (*input, 0, i);
	tmp2 = ft_substr (*input, i + 1, ft_strlen(ft_strchr(*input, '$') + 1));
	new = ft_strjoin_gnl (tmp, tmp2);
	free (*input);
	*input = new;
	free (tmp2);
}
