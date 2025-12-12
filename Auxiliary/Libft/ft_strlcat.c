/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diomende <diomende@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 14:11:20 by diomende          #+#    #+#             */
/*   Updated: 2025/07/09 18:11:38 by diomende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dstsize;

	if (size == 0)
		return (ft_strlen(src));
	dstsize = ft_strlen(dst);
	if (dstsize > size)
		return (ft_strlen(src) + size);
	else
		ft_strlcpy (&dst[dstsize], src, (size - dstsize));
	return (ft_strlen(src) + dstsize);
}
// int main (void)
// {
// 	char s[] = "adeus";
// 	char d[] = "ola";
// 	char s1[] = "adeus";
// 	char d2[] = "ola";

// 	size_t size = 4;
// 	ft_strlcat(d, s, size);
// 	printf("%zu\n", ft_strlcat(d, s1, size));
// 	printf("%s\n", s1);
// 	printf("%s\n", d);
// 	// printf("%d\n", strlcat(d2, s1, size));
// 	// printf("%s\n", s1);
// 	// printf("%s\n", d2);
// }