/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diomende <diomende@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 20:53:39 by diomende          #+#    #+#             */
/*   Updated: 2025/04/22 21:12:45 by diomende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;

	if (dest == src)
		return (dest);
	if (dest > src)
	{
		i = n;
		while (i > 0)
		{
			((unsigned char *)dest)[i - 1] = ((unsigned char *)src)[i - 1];
			i--;
		}
	}
	else
	{
		i = 0;
		while (i < n)
		{
			((unsigned char *) dest)[i] = ((unsigned char *)src)[i];
			i++;
		}
	}
	return (dest);
}

// int main (void)
// {
	// char s[] = "";
	// char d[] = "";
	// char s1[] = "";
	// char d2[] = "";

	// size_t size= 3;
	// ft_memmove(NULL, "ola", size);
	// printf("%s\n", s);
	// printf("%s\n", d);
	// memmove(NULL, "ola", size);
	// printf("%s\n", s1);
	// printf("%s\n", d2);
// }
