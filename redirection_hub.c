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
		if(input_redirect (mstr, cmd))
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
