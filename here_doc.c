#include "minishellD.h"

int	hdoc_rdwr(t_master *mstr, t_cmdlist *cmd, char *del)
{
	char	*hdoc;
	char	*line;
	int		fd;

	hdoc = NULL;
	fd = hdoc_opener (mstr, cmd);
	if (hdoc_signal_setup (fd))
		return (1);
	while (1)
	{
		line = readline ("> ");
		if (write (fd, 0, 0) == -1)
			return (unlink(cmd->filename), 1);
		if (!line)
			return (free(hdoc), close (fd), unlink(cmd->filename), printf("here-document \
delimeted by end-of-file (wanted `%s')\n", del), sign()->hdoc_flag = 1, 1);
		if (!ft_strncmp(del, line, ft_strlen(del) + 1))
			break ;
		hdoc = hdoc_wr_helper(mstr, cmd, hdoc, line);
		if (hdoc == NULL)
			break ;
	}
	if (hdoc)
		write (fd, hdoc, ft_strlen(hdoc));
	return (close (fd), free (hdoc), free(line), 0);
}

char	*hdoc_wr_helper(t_master *mstr, t_cmdlist *cmd, char *hdoc, char *line)
{
	line = ft_strjoin_gnl (line, "\n");
	if (!line)
		alloc_error (&mstr);
	hdoc = ft_strjoin_gnl (hdoc, line);
	if (!hdoc)
	{
		free (line);
		alloc_error (&mstr);
	}
	free (line);
	if (cmd->hdoc_flag == 0)
		expand_hdoc(mstr, &hdoc);
	return (hdoc);
}

void	expand_hdoc(t_master *mstr, char **redir)
{
	int		i;
	char	*key;

	i = 0;
	key = NULL;
	key = get_varkey(*redir);
	while (key)
	{
		if (check_exp(redir, &key, mstr))
		{
			search_and_replace(redir, key, mstr);
		}
		key = get_varkey(*redir);
	}
}

int	hdoc_opener(t_master *mstr, t_cmdlist *cmd)
{
	int		i;
	int		fd;
	char	*tmp;

	i = 0;
	while (1)
	{
		free (cmd->filename);
		tmp = ft_strjoin_gnl(ft_itoa(i), "tmp_heredoc.txt");
		cmd->filename = ft_strjoin_gnl(ft_strdup("src/"), tmp);
		free (tmp);
		if (!cmd->filename)
			alloc_error (&mstr);
		if (access(cmd->filename, F_OK) == -1)
			break ;
		i++;
	}
	fd = open(cmd->filename, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd == -1)
		return (-1);
	return (fd);
}

int	hdoc_handler(t_master *mstr, t_cmdlist *cmd)
{
	int			i;
	t_cmdlist	*ptr;

	i = 0;
	ptr = cmd;
	while (ptr->input[i])
	{
		if (!ft_strncmp (ptr->input[i], "<<", 3))
		{
			if (hdoc_rdwr(mstr, ptr, ptr->input[i + 1]))
			{
				sign()->sig_flag = 1;
				signals();
				return (1);
			}
			if (ptr->input[i + 2])
				unlink(cmd->filename);
		}
		i++;
	}
	return (0);
}
