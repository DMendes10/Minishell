/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diomende <diomende@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 18:23:47 by diomende          #+#    #+#             */
/*   Updated: 2025/04/22 19:05:52 by diomende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free (lst);
}

// void	del(void *c)
// {
// 	free(c);
// }
// int main (void)
// {
// 	t_list *t1 = ft_lstnew("primeiro");
// 	t_list *t2 = ft_lstnew("segundo");
// 	t1->next = t2;
// 	printf(" %s\n", (char *)t2->content);
// 	void del (void *);
// 	ft_lstdelone(t2, del);
// 	printf(" %s\n", (char *)t2->content);
// 	free(t1->next);
// 	free(t1);
// 	return (0);
// }