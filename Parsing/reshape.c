/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reshape.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogo <diogo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 15:27:03 by jomaia            #+#    #+#             */
/*   Updated: 2025/12/12 16:29:20 by diogo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_spaces(char **s)
{
	int	i;
	int	quotes;

	i = 0;
	quotes = 0;
	while ((*s)[i])
	{
		if (((*s)[i] == ' ' || (*s)[i] == -2) && quotes == 0)
			(*s)[i] = SEP;
		else if ((*s)[i] == '\'' || (*s)[i] == '\"')
			quotes = quotes_check((*s)[i], quotes);
		i++;
	}
	i = 0;
	while ((*s)[i])
	{
		if ((*s)[i] == SEP || (*s)[i] == -2)
			return (1);
		i++;
	}
	return (0);
}

int	arr_size(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
		i++;
	return (i);
}

void	free_cmd(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
		free (cmd[i++]);
	free (cmd);
}

void	reshape_split(char **s, char ***cmd, int j, int k)
{
	char	**temp;
	char	**new_arr;
	int		size;
	int		i;

	new_arr = NULL;
	i = 0;
	temp = ft_split(*s, SEP);
	size = arr_size(*cmd) + arr_size(temp) - 1;
	new_arr = ft_calloc(size + 1, sizeof(char *));
	if (!new_arr)
		return ;
	while ((*cmd)[k] && (*cmd)[k] != *s)
	{
		new_arr[i++] = ft_strdup((*cmd)[k++]);
	}
	while (temp[j])
		new_arr[i++] = ft_strdup(temp[j++]);
	k++;
	while ((*cmd)[k])
		new_arr[i++] = ft_strdup((*cmd)[k++]);
	free_cmd (*cmd);
	free_cmd (temp);
	*cmd = new_arr;
}

void	reshaping(t_master *mstr)
{
	int			i;
	t_cmdlist	*node;

	i = 0;
	node = mstr->cmd;
	while (node)
	{
		i = 0;
		while (node->command && node->command[i])
		{
			if (check_spaces(&node->command[i]))
			{
				reshape_split(&node->command[i], &node->command, 0, 0);
			}
			else
				i++;
		}
		node = node->next;
	}
}
