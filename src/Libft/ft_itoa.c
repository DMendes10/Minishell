/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diomende <diomende@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 19:41:35 by diomende          #+#    #+#             */
/*   Updated: 2025/04/23 12:06:47 by diomende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_nbrlen(long nb)
{
	size_t			count;
	unsigned int	i;

	i = (unsigned int) nb;
	count = 0;
	if (nb < 0)
		i = -1 * i;
	while (i > 0)
	{
		i = (i / 10);
		count++;
	}
	return (count);
}

static char	*ft_putnbr(char *s, unsigned int n2, size_t len, int neg)
{
	while (len > 0)
	{
		s[len -1 + neg] = n2 % 10 + '0';
		n2 = n2 / 10;
		len--;
	}
	if (neg > 0)
		s[0] = '-';
	return (s);
}

char	*ft_itoa(int n)
{
	int				neg;
	unsigned int	n2;
	char			*s;
	size_t			len;

	neg = 0;
	len = ft_nbrlen (n);
	n2 = (unsigned int) n;
	len = ft_nbrlen(n);
	if (n == 0)
	{
		s = ft_calloc (sizeof(char), 2);
		s[0] = '0';
		return (s);
	}
	if (n < 0)
	{
		neg = 1;
		n2 = -n;
	}
	s = ft_calloc (sizeof(char), neg + len + 1);
	if (!s)
		return (NULL);
	ft_putnbr(s, n2, len, neg);
	return (s);
}

// int main ()
// {
// 	printf("%s\n", ft_itoa(0));
// }
