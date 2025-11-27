#include "parser.h"

int	split_size(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

char	*quote_to_sep(char	**s)
{
	int		i;
	int		quotes;

	i = 0;
	quotes = 0;
	while ((*s)[i])
	{
		if ((*s)[i] == '\'' && (quotes == 0 || quotes == 1))
		{
			quotes = quotes_check((*s)[i], quotes);
			(*s)[i] = -1;
		}
		else if((*s)[i] == '\"' && (quotes == 0 || quotes == 2))
		{
			quotes = quotes_check((*s)[i], quotes);
			(*s)[i] = -1;
		}
		i++;
	}
	return (*s);
}

void	split_quotes(char **s)
{
	int	i;
	char	**temp;
	char	*to_free;

	i = 1;
	if (!ft_strncmp(*s, "", ft_strlen(*s)))
		return ;
	temp = ft_split(quote_to_sep(s), -1);
	free(*s);
	if (!temp[0])
	{
		*s = ft_strdup("");
		free_array(temp);
		return ;
	}
	*s = ft_strdup(temp[0]);
	if (split_size(temp) > 1)
	{
		while (temp[i])
		{
			to_free = *s;
			*s = ft_strjoin(to_free, temp[i++]);
			free (to_free);
		}
	}
	free_array(temp);
}



void	rem_quotes(t_master *master)
{
	int	i;
	t_cmdlist	*node;

	i = 0;
	node = master->cmd;
	while (node)
	{
		i = 0;
		while (node->command && node->command[i])
			split_quotes(&node->command[i++]);
		i = 0;
		while (node->input && node->input[i])
			split_quotes(&node->input[i++]);
		i = 0;
		while (node->output && node->output[i])
			split_quotes(&node->output[i++]);
		i = 0;
		node = node->next;
	}
}
