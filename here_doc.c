#include "minishellD.h"

int	hdoc_rdwr(char *del)
{
	char	*hdoc;
	char	*line;
	int		fd;

	hdoc = ft_strdup("");
	fd = open("tmp_heredoc.txt", O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd == -1)
		return (1);
	while(1)
	{
		line = readline ("> ");
		if (line == NULL)
			return (free(hdoc), printf("here-document delimeted by end-of-file (wanted `%s')", del), 1);
			// ou perror()?
		if (!ft_strncmp(del, line, ft_strlen(del)))
			break ;
		hdoc = ft_strjoin_gnl (hdoc, line);
		if (hdoc == NULL)
			break ;
	}
	write (fd, hdoc, ft_strlen(hdoc));
	free (line);
	free (hdoc);
	close (fd);
	return (0);
}

int	hdoc_handler(t_master *mstr, t_cmdlist *cmd)
{
	int i;

	i = 0;
	while (cmd->input[i])
	{
		if (!ft_strncmp (cmd->input[i], "<<", 3))
		{
			if (hdoc_rdwr(cmd->input[i + 1]))
				return (1);
			// pensar melhor nisto (no return)
			mstr->data->fdin = open("tmp_heredoc.txt", O_RDONLY);
			if (mstr->data->fdin == -1)
			{
				printf("%s", cmd->input[i + 1]);
				perror(":");
				return (1);
			}
			dup2 (mstr->data->fdin, STDIN_FILENO);
			unlink ("tmp_heredoc.txt");
		}
		i++;
		close (mstr->data->fdin);
	}
	return (0);
}
