/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diomende <diomende@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 16:46:36 by diomende          #+#    #+#             */
/*   Updated: 2025/07/07 18:17:28 by diomende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_next_line(int fd)
{
	static char		buffer[BUFFER_SIZE + 1];
	int				counter;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	if (*buffer != '\0')
		line = ft_strjoin_gnl (line, buffer);
	while (ft_newline_finder(line) == -1)
	{
		counter = read (fd, buffer, BUFFER_SIZE);
		if (counter < 0)
		{
			buffer[0] = '\0';
			return (free(line), NULL);
		}
		if (counter == 0)
			break ;
		buffer[counter] = '\0';
		line = ft_strjoin_gnl (line, buffer);
	}
	line = ft_line_builder (line);
	ft_storage_builder (buffer);
	return (line);
}

// int main(void)
// {
// 	int	i;
// 	int	fd = open("read_error.txt", O_RDONLY);
// 	char *line;

// 	i = 0;

// 	while (i < 1)
// 	{
// 		line = get_next_line(fd);
// 		printf("%s", line);
// 		free(line);
// 		i++;
// 	}
// 	close(fd);
// }