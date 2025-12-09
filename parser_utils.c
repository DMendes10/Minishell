/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogo <diogo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 15:26:31 by jomaia            #+#    #+#             */
/*   Updated: 2025/12/09 14:49:13 by diogo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	quotes_check(char c, int quotes)
{
	if (c == '\'')
	{
		if (quotes == 0)
			quotes = 1;
		else if (quotes == 1)
			quotes = 0;
	}
	else if (c == '\"')
	{
		if (quotes == 0)
			quotes = 2;
		else if (quotes == 2)
			quotes = 0;
	}
	return (quotes);
}

char	**split_args(char *input)
{
	int		i;
	int		quotes;
	char	**res;

	i = 0;
	quotes = 0;
	while (input[i])
	{
		if ((input[i] == ' ' || input[i] == '	') && !quotes)
			input[i] = SEP;
		else if (input[i] == '\'' || input[i] == '\"')
			quotes = quotes_check(input[i], quotes);
		i++;
	}
	res = ft_split(input, SEP);
	return (res);
}

char	*get_input(t_master *mstr, char *prompt)
{
	char	*input;

	input = readline (prompt);
	if (input && input[0])
		add_history (input);
	else if (!input)
	{
		ft_putstr_fd ("Exit\n", 1);
		exit_minishell (&mstr, sign()->exit_code);
	}
	return (input);
}
