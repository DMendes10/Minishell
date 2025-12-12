/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diomende <diomende@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:55:42 by diomende          #+#    #+#             */
/*   Updated: 2025/04/22 19:10:41 by diomende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	new->next = *lst;
	*lst = new;
}

// int main (void)
// {
// 	t_list *t1 = ft_lstnew("primeiro");
// 	t_list *t2 = ft_lstnew("segundo");
// 	ft_lstadd_front(&t1, t2);
// 	printf(" %s\n", (char *)t2->content);
// 	printf(" %s\n", (char *)t2->next->content);
// 	free(t1->next);
// 	free(t1);
// 	return (0);
// }