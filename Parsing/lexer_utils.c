/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomaia <jomaia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 15:26:00 by jomaia            #+#    #+#             */
/*   Updated: 2025/12/08 15:26:01 by jomaia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	quote_checker(char c, int quotes)
{
	if (c == '\'')
	{
		if (quotes == 1)
			quotes = 0;
		else if (quotes == 0)
			quotes = 1;
	}
	if (c == '\"')
	{
		if (quotes == 2)
			quotes = 0;
		else if (quotes == 0)
			quotes = 2;
	}
	return (quotes);
}
