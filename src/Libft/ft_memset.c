/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diomende <diomende@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 20:50:03 by diomende          #+#    #+#             */
/*   Updated: 2025/04/22 14:03:12 by diomende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned int	i;
	unsigned char	*s1;

	i = 0;
	s1 = (unsigned char *) s;
	while (i < n)
	{
		i[s1] = (unsigned char) c;
		i++;
	}
	return (s);
}

// int main (void)
// {
// 	int i = 0;
// 	size_t size = 3;
// 	unsigned char* c = malloc(size);
// 	ft_memset(c ,1, size);

// 	while (i<size)
// 	{
// 		printf("%d", i[c]);
// 		i++;
// 	}
// 	free(c);
// }