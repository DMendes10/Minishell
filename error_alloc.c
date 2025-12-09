/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_alloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogo <diogo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 15:02:19 by diogo             #+#    #+#             */
/*   Updated: 2025/12/09 15:02:20 by diogo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishellD.h"

void	alloc_error(t_master **mstr)
{
	perror("ERROR");
	exit_minishell (mstr, 1);
}

void	alloc_error_exit(t_master *master, char **array)
{
	free_array (array);
	alloc_error (&master);
}

void	exec_error_handler(t_master *mstr, t_cmdlist *cmd, char \
*path, char **env)
{
	if (path && (path[0] == '/' || path[0] == '.'))
	{
		ft_putstr_fd (cmd->command[0], 2);
		ft_putstr_fd (": Is a directory\n", 2);
		sign()->exit_code = 126;
	}
	else
		perror (cmd->command[0]);
	free_array(env);
	exit_minishell(&mstr, sign()->exit_code);
}
