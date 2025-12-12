/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diomende <diomende@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 20:54:55 by diomende          #+#    #+#             */
/*   Updated: 2025/08/27 17:38:03 by diomende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	len;
	size_t	i;

	len = ft_strlen(src);
	i = 0;
	if (len + 1 < size)
	{
		while (src[i])
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	else if (size != 0)
	{
		while (i < size -1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (len);
}

// int main (void)
// {
// 	char s[] = "adeus";
// 	char d[] = "ola";
// 	char s1[] = "adeus";
// 	char d2[] = "ola";

// 	size_t size= 3;
// 	ft_strlcpy(d, s, size);
// 	printf("%s\n", s);
// 	printf("%s\n", d);
// 	// strlcpy(d2, s1, size);
// 	// printf("%s\n", s1);
// 	// printf("%s\n", d2);
// }
