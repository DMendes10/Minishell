/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogo <diogo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 15:01:44 by diogo             #+#    #+#             */
/*   Updated: 2025/12/09 15:01:45 by diogo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishellD.h"

t_envlst	*ft_new_env_key(char *envkey)
{
	t_envlst	*node;

	node = malloc(sizeof(t_envlst));
	if (!node)
		return (NULL);
	node->token = ft_strdup(envkey);
	node->var = NULL;
	node->next = NULL;
	return (node);
}

void	delete_env_node(t_envlst *ptr, t_envlst *last, t_master **mstr)
{
	if (!last || ptr == last)
		(*mstr)->env = ptr->next;
	else
		last->next = ptr->next;
	free(ptr->token);
	if (ptr->var)
		free(ptr->var);
	free(ptr);
}

int	key_check(char *key)
{
	int	i;

	i = 1;
	if (!ft_isalpha(key[0]) && key[0] != '_')
		return (1);
	while (key[i] && key[i] != '=')
	{
		if (!ft_isalnum (key[i]) && key[0] != '_')
			break ;
		i++;
	}
	if (key[i] && key[i] == '+')
	{
		if (key[i + 1] && key[i + 1] == '=')
			return (0);
	}
	else if (key[i] && key[i] == '=')
		return (0);
	else if (!key[i])
		return (0);
	return (1);
}

int	str_valid_nbr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

char	**envlst_to_char(t_master *mstr)
{
	t_envlst	*ptr;
	char		**env;
	int			i;

	ptr = mstr->env;
	i = 0;
	while (ptr)
	{
		if (ptr->var)
			i++;
		ptr = ptr->next;
	}
	env = malloc (sizeof (char *) * (i + 1));
	if (!env)
		alloc_error (&mstr);
	i = 0;
	ptr = mstr->env;
	while (ptr)
	{
		if (ptr->var)
			env[i++] = ft_strjoin_gnl (ft_strjoin(ptr->token, "="), ptr->var);
		ptr = ptr->next;
	}
	env[i] = NULL;
	return (env);
}
