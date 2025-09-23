/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diomende <diomende@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 14:00:05 by diomende          #+#    #+#             */
/*   Updated: 2025/04/22 14:02:04 by diomende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*d;
	unsigned char	*s;

	i = 0;
	d = (unsigned char *) dest;
	s = (unsigned char *) src;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}

// int main (void)
// {
	// char s[] = "";
	// char d[] = "";
	// char s1[] = "";
	// char d1[] = "";

	// size_t size= 3;
	// ft_memcpy(NULL, "Hello", size);
	// memcpy (NULL, "Hello", size);
// 	printf("%s\n", s);
// 	printf("%s\n", d);
// 	printf("%s\n", s1);
// 	printf("%s\n", d1);
// }