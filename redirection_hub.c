/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_hub.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogo <diogo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 15:04:37 by diogo             #+#    #+#             */
/*   Updated: 2025/12/09 15:04:38 by diogo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishellD.h"

void	redir_handler(t_master *mstr, t_cmdlist *cmd)
{
	dup2(mstr->data->last_fd, STDIN_FILENO);
	close (mstr->data->last_fd);
	if (cmd->next)
	{
		dup2(mstr->data->pipefd[1], STDOUT_FILENO);
		close (mstr->data->pipefd[0]);
		close (mstr->data->pipefd[1]);
	}
	if (cmd->input && input_redirect (mstr, cmd))
		exit_minishell(&mstr, 1);
	if (cmd->output && output_redirect (mstr, cmd))
		exit_minishell(&mstr, 1);
}

int	built_in_redir(t_master *mstr, t_cmdlist *cmd, int in, int out)
{
	if (cmd->input)
	{
		if (input_redirect (mstr, cmd))
		{
			dup2(in, STDIN_FILENO);
			dup2(out, STDOUT_FILENO);
			close(in);
			close(out);
			return (1);
		}
	}
	if (cmd->output)
	{
		if (output_redirect (mstr, cmd))
		{
			dup2(in, STDIN_FILENO);
			dup2(out, STDOUT_FILENO);
			close(in);
			close(out);
			return (1);
		}
	}
	return (0);
}

int	input_redirect(t_master *mstr, t_cmdlist *cmd)
{
	int	i;

	i = 0;
	while (cmd->input[i])
	{
		if (!ft_strncmp (cmd->input[i], "<", 2))
		{
			if (redir_expansion (mstr, cmd->input, i + 1))
				return (printf("%s: ambiguous redirec\
					t\n", cmd->input[i + 1]), 1);
			mstr->data->fdin = open(cmd->input[i + 1], O_RDONLY);
			if (mstr->data->fdin < 0)
				return (perror(cmd->input[i + 1]), sign()->exit_code = 1, 1);
			dup2 (mstr->data->fdin, STDIN_FILENO);
			close (mstr->data->fdin);
		}
		else if (!ft_strncmp (cmd->input[i], "<<", 2))
		{
			if (h_doc_redir (mstr, cmd, i))
				return (1);
		}
		i += 2;
	}
	return (0);
}

int	output_redir_helper(t_master *mstr, t_cmdlist *cmd, int i)
{
	if (redir_expansion (mstr, cmd->output, i + 1))
		return (printf("%s: ambiguous redirect\n", cmd->output[i + 1]), 1);
	mstr->data->fdout = open (cmd->output[i + 1], O_WRONLY \
| O_CREAT | O_TRUNC, 0644);
	if (mstr->data->fdout == -1)
		return (perror(cmd->output[i + 1]), sign()->exit_code = 1, 1);
	dup2 (mstr->data->fdout, STDOUT_FILENO);
	close (mstr->data->fdout);
	return (0);
}

int	output_redirect(t_master *mstr, t_cmdlist *cmd)
{
	int	i;

	i = 0;
	while (cmd->output[i])
	{
		if (!ft_strncmp (cmd->output[i], ">", 2))
		{
			if (output_redir_helper (mstr, cmd, i))
				return (1);
		}
		else if (!ft_strncmp (cmd->output[i], ">>", 2))
		{
			if (redir_expansion (mstr, cmd->output, i + 1))
				return (printf("%s: ambiguous redirec\
					t\n", cmd->output[i + 1]), 1);
			mstr->data->fdout = open (cmd->output[i + 1], \
O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (mstr->data->fdout == -1)
				return (perror(cmd->output[i + 1]), sign()->exit_code = 1, 1);
			dup2 (mstr->data->fdout, STDOUT_FILENO);
			close (mstr->data->fdout);
		}
		i += 2;
	}
	return (0);
}
