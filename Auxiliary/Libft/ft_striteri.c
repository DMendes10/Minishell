/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diomende <diomende@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 21:03:36 by diomende          #+#    #+#             */
/*   Updated: 2025/04/22 14:09:18 by diomende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f) (unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	if (!s || !f)
		return ;
	while (s[i])
	{
		f (i, &s[i]);
		i++;
	}
}

// void	ola(unsigned int i, char *c)
// {
// 	c = i;
// }

// int main ()
// {
// 	printf("%s", ft_strmapi("ola amigo", ola));
// }
