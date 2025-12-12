/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diomende <diomende@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 20:59:08 by diomende          #+#    #+#             */
/*   Updated: 2025/04/22 14:17:23 by diomende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;

	i = 0;
	if (!*little)
		return ((char *)big);
	while (big[i] && i < len)
	{
		if (len - i < ft_strlen(little))
			return (NULL);
		else if (ft_memcmp(little, &big[i], ft_strlen(little)) == 0)
			return ((char *)&big[i]);
		i++;
	}
	return (NULL);
}

// int main ()
// {
// 	printf("%s\n", ft_strnstr("aaabcabcd", "cd", 8));
// }