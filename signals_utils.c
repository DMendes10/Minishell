/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomaia <jomaia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 15:27:10 by jomaia            #+#    #+#             */
/*   Updated: 2025/12/08 15:27:11 by jomaia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishellD.h"

t_sig	*sign(void)
{
	static t_sig	sign;

	return (&sign);
}

void	init_sign(void)
{
	sign()->exit_code = 0;
	sign()->sig_flag = 1;
	sign()->hdoc_flag = 0;
}
