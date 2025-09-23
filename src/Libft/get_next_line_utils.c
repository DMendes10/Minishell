/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diomende <diomende@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 16:46:58 by diomende          #+#    #+#             */
/*   Updated: 2025/07/10 17:16:52 by diomende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_line_builder(char *s)
{
	int		i;
	int		line_size;
	char	*line;

	if (!s || !*s)
		return (NULL);
	line_size = ft_newline_finder (s);
	if (line_size == -1)
		line_size = ft_strlen(s) - 1;
	line = malloc ((line_size + 2) * sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (s[i] != '\n' && s[i] != '\0')
	{
		line[i] = s[i];
		i++;
	}
	if (s[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	free (s);
	return (line[i] = '\0', line);
}

void	ft_storage_builder(char *buffer)
{
	int		line_size;
	int		i;
	int		j;

	if (!buffer || !*buffer)
		return ;
	line_size = ft_newline_finder(buffer) + 1;
	j = 0;
	if (line_size == 0)
	{
		while (j < BUFFER_SIZE + 1)
			buffer[j++] = '\0';
		return ;
	}
	i = line_size;
	while (buffer[i] != '\0')
		buffer[j++] = buffer[i++];
	while (j < BUFFER_SIZE + 1)
		buffer[j++] = '\0';
	return ;
}

size_t	ft_strlen_gnl(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*s3;
	int		i;
	int		j;

	if (!s2)
		return (NULL);
	s3 = malloc(sizeof (char) * (ft_strlen_gnl(s1) + ft_strlen_gnl(s2) + 1));
	if (!s3)
		return (NULL);
	i = 0;
	while (s1 && s1[i])
	{
		s3[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		s3[i + j] = s2[j];
		j++;
	}
	s3[i + j] = '\0';
	free (s1);
	return (s3);
}

int	ft_newline_finder(char *s)
{
	int	i;

	if (!s)
		return (-1);
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}
