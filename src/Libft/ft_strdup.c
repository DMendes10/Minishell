/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diomende <diomende@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 21:00:21 by diomende          #+#    #+#             */
/*   Updated: 2025/04/21 21:00:33 by diomende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*s2;

	len = ft_strlen(s);
	s2 = malloc((sizeof (char)) * len +1);
	if (s2 == NULL)
		return (NULL);
	ft_strlcpy(s2, s, len + 1);
	return (s2);
}

// int main ()
// {
// 	printf("%s\n", ft_strdup("ola"));
// }