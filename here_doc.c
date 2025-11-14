#include "minishellD.h"

int	hdoc_rdwr(t_master *mstr, t_cmdlist *cmd, char *del)
{
	char	*hdoc;
	char	*line;
	int		fd;
	int 	i;

	i = 0;
	(void) mstr;
	hdoc = ft_strdup("");
	while (1)
	{
		free (cmd->filename);
		cmd->filename = ft_strjoin_gnl(ft_itoa(i), "tmp_heredoc.txt");
		if (access(cmd->filename, F_OK) == -1)
			break;
		i++;
	}
	fd = open(cmd->filename, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd == -1)
		return (1);
	while(1)
	{
		line = readline ("> ");
		if (line == NULL)
			return (free(hdoc), unlink(cmd->filename), printf("here-document delimeted by end-of-file (wanted `%s')\n", del), 1);
			// ou perror()?
		if (!ft_strncmp(del, line, ft_strlen(del) + 1))
			break ;
		line = ft_strjoin_gnl (line, "\n");
		hdoc = ft_strjoin_gnl (hdoc, line);
		free (line);
		if (hdoc == NULL)
			break ;
	}
	write (fd, hdoc, ft_strlen(hdoc));
	close (fd);
	// cmd->filename = ft_strdup (mstr->data->filename);
	return (free(line), free(hdoc), 0);
}

int	hdoc_handler(t_master *mstr, t_cmdlist *cmd)
{
	int i;
	t_cmdlist *ptr;

	i = 0;
	ptr = cmd;
	while (ptr->input[i])
	{
		if (!ft_strncmp (ptr->input[i], "<<", 3))
		{
			if (hdoc_rdwr(mstr, ptr, ptr->input[i + 1]))
				return (1);
			if (ptr->input[i + 2])
				unlink(cmd->filename);
			// pensar melhor nisto (no return)
			// mstr->data->fdin = open(mstr->data->filename, O_RDONLY);
			// if (mstr->data->fdin == -1)
			// {
			// 	// printf("%s", cmd->input[i + 1]);
			// 	perror("here-document error");
			// 	return (1);
			// }
			// dup2 (mstr->data->fdin, STDIN_FILENO);
			// unlink (mstr->data->filename);
			// close (mstr->data->fdin);
		}
		i++;
	}
	return (0);
}
