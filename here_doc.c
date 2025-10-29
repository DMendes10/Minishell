#include "minishellD.h"

void hdoc_rdwr(char *del)
{
    char *hdoc;
    char *line;
    int     fd;

    hdoc = ft_strdup("");
    fd = open("tmp_heredoc.txt", O_WRONLY | O_CREAT | O_TRUNC, 0600);
    if (fd == -1)
		return_error();
    while(1)
    {
        line = readline (">");
        if (line == NULL)
            return (free(hdoc));
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
    return ;
}
