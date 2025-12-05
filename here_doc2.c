#include "minishellD.h"

int	hdoc_signal_setup(int fd)
{
	sign()->fd = fd;
	sign()->sig_flag = 2;
	signals();
	if (fd == -1)
		return (1);
	return (0);
}

int	h_doc_redir(t_master *mstr, t_cmdlist *cmd, int i)
{
	if (!cmd->input[i + 2])
	{
		mstr->data->fdin = open(cmd->filename, O_RDONLY);
		if (mstr->data->fdin == -1)
		{
			perror("here-document error");
			return (1);
		}
		dup2 (mstr->data->fdin, STDIN_FILENO);
		close (mstr->data->fdin);
		unlink (cmd->filename);
	}
	return (0);
}
