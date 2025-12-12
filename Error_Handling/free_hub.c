/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_hub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogo <diogo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 15:03:43 by diogo             #+#    #+#             */
/*   Updated: 2025/12/12 16:29:20 by diogo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_master(t_master **master)
{
	if ((*master)->cmd)
		free_cmdlst((*master)->cmd);
	if ((*master)->env)
		free_envlst((*master)->env);
	if ((*master)->data)
	{
		if ((*master)->data->svd_stdin >= 0)
			close((*master)->data->svd_stdin);
		free ((*master)->data->pid);
		free ((*master)->data);
	}
}

void	free_envlst(t_envlst *envlst)
{
	t_envlst	*ptr;

	ptr = envlst;
	while (ptr)
	{
		envlst = (envlst)->next;
		free (ptr->token);
		free (ptr->var);
		free (ptr);
		ptr = envlst;
	}
}

void	free_cmdlst(t_cmdlist *cmdlst)
{
	t_cmdlist	*ptr;

	ptr = cmdlst;
	while (ptr)
	{
		cmdlst = (cmdlst)->next;
		free_array (ptr->command);
		free_array (ptr->input);
		free_array (ptr->output);
		free (ptr->filename);
		free (ptr);
		ptr = cmdlst;
	}
}

void	exit_minishell(t_master **mstr, int exit_code)
{
	free_master(mstr);
	free (*mstr);
	exit (exit_code);
}

void	reset_master(t_master **master)
{
	free_cmdlst((*master)->cmd);
	(*master)->cmd = NULL;
	free ((*master)->data->pid);
	ft_memset ((*master)->data, 0, sizeof (t_edata));
	(*master)->data->svd_stdin = -1;
	sign()->hdoc_flag = 0;
}
