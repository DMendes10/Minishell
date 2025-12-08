/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomaia <jomaia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 15:27:36 by jomaia            #+#    #+#             */
/*   Updated: 2025/12/08 15:27:37 by jomaia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishellD.h"

void	free_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		free(args[i++]);
	free(args);
}

void	print_err(char *error, char **arg)
{
	free_args(arg);
	ft_putstr_fd(error, 2);
}
