#include "minishellD.h"

int	hdoc_rdwr(t_master *mstr, char *del)
{
	char	*hdoc;
	char	*line;
	int		fd;
	int 	i;

	i = 0;
	hdoc = ft_strdup("");
	while (1)
	{
		free (mstr->data->filename);
		mstr->data->filename = ft_strjoin_gnl(ft_itoa(i), "tmp_heredoc.txt");
		if (access(mstr->data->filename, F_OK) == -1)
			break;
		i++;
	}
	fd = open(mstr->data->filename, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd == -1)
		return (1);
	while(1)
	{
		line = readline ("> ");
		if (line == NULL)
			return (free(hdoc), unlink(mstr->data->filename), printf("here-document delimeted by end-of-file (wanted `%s')\n", del), 1);
			// ou perror()?
		if (!ft_strncmp(del, line, ft_strlen(del)))
			break ;
		line = ft_strjoin_gnl (line, "\n");
		hdoc = ft_strjoin_gnl (hdoc, line);
		free (line);
		if (hdoc == NULL)
			break ;
	}
	write (fd, hdoc, ft_strlen(hdoc));
	close (fd);
	return (free(line), free(hdoc), 0);
}

int	hdoc_handler(t_master *mstr, t_cmdlist *cmd)
{
	int i;

	i = 0;
	while (cmd->input[i])
	{
		if (!ft_strncmp (cmd->input[i], "<<", 3))
		{
			if (hdoc_rdwr(mstr, cmd->input[i + 1]))
				return (1);
			// pensar melhor nisto (no return)
			mstr->data->fdin = open(mstr->data->filename, O_RDONLY);
			if (mstr->data->fdin == -1)
			{
				// printf("%s", cmd->input[i + 1]);
				perror("here-document error");
				return (1);
			}
			dup2 (mstr->data->fdin, STDIN_FILENO);
			unlink (mstr->data->filename);
			close (mstr->data->fdin);
		}
		i++;
	}
	return (0);
}
