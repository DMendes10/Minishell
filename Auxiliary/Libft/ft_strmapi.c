/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diomende <diomende@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 21:02:54 by diomende          #+#    #+#             */
/*   Updated: 2025/04/23 16:58:32 by diomende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*s2;

	i = 0;
	if (!s || !f)
	{
		return (NULL);
	}
	s2 = ft_calloc (sizeof(char), ft_strlen(s) + 1);
	if (!s2)
		return (NULL);
	while (s[i])
	{
		s2[i] = f (i, s[i]);
		i++;
	}
	return (s2);
}

// char	ola(unsigned int i, char c)
// {
// 	c = c + i;
// 	return (c);
// }

// int main ()
// {
// 	printf("%s", ft_strmapi("ola amigo", ola));
// }