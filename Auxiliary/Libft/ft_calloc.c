/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diomende <diomende@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 20:59:54 by diomende          #+#    #+#             */
/*   Updated: 2025/04/23 16:37:56 by diomende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*s;

	if (size == 0 || nmemb == 0)
		return (malloc(0));
	if (size > INT_MAX / nmemb)
		return (NULL);
	s = malloc(nmemb * size);
	if (s == NULL)
		return (NULL);
	ft_bzero(s, (nmemb * size));
	return (s);
}

// int main ()
// {
// 	printf("%s\n", ft_calloc(1, 9));
// }