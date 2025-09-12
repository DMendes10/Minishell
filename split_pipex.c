/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogo <diogo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 19:28:14 by diomende          #+#    #+#             */
/*   Updated: 2025/09/12 15:39:53 by diogo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_makestring(const char *s, char c, size_t *i)
{
	size_t	size;
	char	*s2;
	int		quotes;

	quotes = 0;
	size = 0;
	while (s[size] != c && s[size] != '\0')
	{
		size++;
		if (s[size] == '\'')
		{
			quotes++;
			size++;
			while (s[size] != '\'')
				size++;
		}
	}
	s2 = ft_calloc (sizeof (char), (size - quotes * 2) + 1);
	if (s2 == NULL)
		return (NULL);
	ft_strlcpy_quotes (s2, s, (size - quotes * 2) + 1);
	(*i) += quotes * 2;
	return (s2);
}

char	*ft_makestring_quote(const char *s, size_t *i)
{
	size_t	start;
	size_t	len;
	char	*word;

	(*i)++;
	start = *i;
	while (s[*i] && s[*i] != '\'')
		(*i)++;
	len = *i - start;
	word = ft_calloc(len + 1, sizeof(char));
	if (!word)
		return (NULL);
	ft_strlcpy(word, s + start, len + 1);
	if (s[*i] == '\'')
		(*i)++;
	return (word);
}

char	**ft_minisplit(char **a, char const *s, char c)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (!s[i])
			break ;
		if (s[i] == '\'')
			a[j] = ft_makestring_quote (s, &i);
		else
		{
			a[j] = ft_makestring(&s[i], c, &i);
			i += ft_strlen(a[j]);
		}
		if (!a[j])
			return (free_array(a), NULL);
		j++;
	}
	return (a);
}

char	**ft_split_pipex(char const *s, char c)
{
	char	**array;

	if (!s)
		return (NULL);
	if (ft_count_words_pipex(s, c, 0) < 1)
		return (NULL);
	array = ft_calloc (sizeof(char *), ft_count_words_pipex(s, c, 0) + 1);
	if (array == NULL)
		return (NULL);
	ft_minisplit(array, s, c);
	return (array);
}

size_t	ft_strlcpy_quotes(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (size == 0)
		return (ft_strlen (src));
	while (i < size -1 && src[j])
	{
		while (src[j] == '\'')
			j++;
		dst[i] = src[j];
		j++;
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}

void	free_array(char **s)
{
	size_t	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		free (s[i]);
		i++;
	}
	free (s);
}

size_t	ft_count_words_pipex(const char *a, char c, int i)
{
	size_t	count;

	count = 0;
	while (a[i])
	{
		if (a[i] && a[i] != '\'' && a[i - 1] != '\'' && a[i] != c)
			count++;
		while (a[i] && a[i] != c && a[i] != '\'')
			i++;
		while (a[i] == c)
			i++;
		if (a[i] == '\'')
		{
			if (a[i - 1] == c)
				count++;
			i++;
			if (end_quote_check (a, i))
				while (a[i] != '\'')
					i++;
			else
				return (0);
			i++;
		}
	}
	return (count);
}

int	end_quote_check(const char *s, int i)
{
	while (s[i])
	{
		if (s[i] == '\'')
			return (1);
		i++;
	}
	return (0);
}