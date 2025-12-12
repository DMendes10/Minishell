/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diomende <diomende@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 21:02:21 by diomende          #+#    #+#             */
/*   Updated: 2025/04/22 14:14:45 by diomende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (i < n && s1[i] && s2[i])
	{
		if ((unsigned char) s1[i] != (unsigned char) s2[i])
			return ((unsigned char) s1[i] - (unsigned char)(s2[i]));
		i++;
	}
	if (i < n)
		return ((unsigned char) s1[i] - (unsigned char)(s2[i]));
	else
		return (0);
}

// int main ()
// {
// 	printf("%d\n", ft_strncmp("banana", "bananA", 7));
// }