/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diomende <diomende@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 14:16:03 by diomende          #+#    #+#             */
/*   Updated: 2025/04/23 16:44:46 by diomende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*s2;

	if (!s)
		return (NULL);
	if (start > ft_strlen((char *)s))
		return (ft_strdup(""));
	if (len > ft_strlen((char *)s) - start)
		len = ft_strlen((char *)s) - start;
	s2 = malloc(sizeof (char) * (len + 1));
	if (s2 == NULL)
		return (NULL);
	ft_strlcpy(s2, &s[start], len + 1);
	return (s2);
}

// int main ()
// {
// 	printf("%s\n", ft_substr("quero uma switch2", 10, 7));
// }