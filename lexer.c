/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomaia <jomaia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 17:10:49 by jomaia            #+#    #+#             */
/*   Updated: 2025/09/25 17:43:16 by jomaia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	ft_count_args(char const *s, char c, int quotes)
{
	size_t	i;
	size_t	isarg;
	size_t	args;

	args = 0;
	i = 0;
	isarg = 0;
	while (s[i])
	{
		if (s[i] != c && isarg == 0)
		{
			args++;
			isarg++;
		}
		if (s[i] == c && isarg == 1)
			isarg--;
		i++;
	}
	return (args);
}

char	**lexer(char *input)
{
	int		i;
	int		quotes;
	char	**cmdtable;
	int		arg;
	
	i = 0;
	arg = 0;
	while (input[i++])
	{

	}
	
}