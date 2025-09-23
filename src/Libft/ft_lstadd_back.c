/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diomende <diomende@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 18:06:45 by diomende          #+#    #+#             */
/*   Updated: 2025/04/23 17:02:19 by diomende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (!new || !lst)
		return ;
	last = *lst;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	else
	{
		while (last->next != NULL)
			last = last->next;
		last->next = new;
	}
}

// int main()
// {
// 	t_list t1;
// 	t_list t2;
// 	t_list t3;
// 	t_list t4;
// 	t_list t5;
// 	t_list	*node;
// 	t1.next = &t2;
// 	t2.next = &t3;
// 	t3.next = &t4;
// 	t4.next = NULL;
// 	t5.next = NULL;
// 	node = &t1;
// 	printf("%p\n", t4.next);
// 	ft_lstadd_back(&node, &t5);
// 	printf("%p\n", t4.next);
// 	printf("%p\n", &t5);
// }