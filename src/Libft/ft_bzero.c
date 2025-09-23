/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diomende <diomende@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 20:52:13 by diomende          #+#    #+#             */
/*   Updated: 2025/04/21 20:52:35 by diomende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned int	i;
	unsigned char	*c;

	c = (unsigned char *) s;
	i = 0;
	while (i < n)
	{
		c[i] = 0;
		i++;
	}
}

// int main (void)
// {
// 	char s[] = "ola";

// 	size_t size= 0;
// 	ft_bzero(s, size);
// 	char p[] = "ola";
// 	bzero(p, size);
// 	printf("%s\n", s);
// 	printf("%s\n", p);
// }