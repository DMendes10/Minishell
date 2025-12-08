/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomaia <jomaia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 15:26:16 by jomaia            #+#    #+#             */
/*   Updated: 2025/12/08 15:26:17 by jomaia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	ft_lst_add_back(t_cmdlist **stack, t_cmdlist *node)
{
	t_cmdlist	*last;

	if (!stack || !node)
		return ;
	if (*stack == NULL)
		*stack = node;
	else
	{
		last = ft_lstlast(*stack);
		last->next = node;
	}
	node->next = NULL;
}
