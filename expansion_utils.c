#include "parser.h"
#include"minishellD.h"

int	get_keysize(char *key)
{
	int	size;

	size = 0;
	while(ft_isalnum(key[size]) || key[size] != '_')
	{
		size++;
	}
	return (size);
}

char	*get_varkey(char *s)
{
	int		i;
	int		quotes;
	char	*key;

	i = 0;
	quotes = 0;
	key = NULL;
	while (s[i])
	{
		if (s[i] == '$' && quotes != 1)
		{
			key = ft_substr(s, i, get_keysize(&s[i]));
			return(key);
		}
		else if (s[i] == '\'' || s[i] == '\"')
			quotes_check(s[i], quotes);
		i++;
	}
	return (key);
}

int	get_varkey_cmd(t_cmdlist **cmdlist, t_expansion *expansion)
{
	t_cmdlist	*node;
	int			i;

	i = 0;
	node = *cmdlist;
	expansion->key = NULL;
	while(node)
	{
		i = 0;
		while (node->command[i])
		{
			expansion->key = get_varkey(node->command[i]);
			if (expansion->key)
			{
				expansion->s = node->command[i];
				return (1);
			}
		}
		node = node->next;
	}
	return (0);
}

int	get_varkey_input(t_cmdlist **cmdlist, t_expansion *expansion, int i)
{
	t_cmdlist	*node;

	expansion->key = NULL;
	node = *cmdlist;
	while(node)
	{
		i = 0;
		while (node->input[i])
		{
			if (ft_strncmp(node->input[i], "<<", 2))
				i = i + 2;
			else
			{
				expansion->key = get_varkey(node->input[i]);
				if (expansion->key)
				{
					expansion->s = node->input[i];
					return (1);
				}
			}
			node = node->next;
		}
	}
	return (0);
}

int	get_varkey_output(t_cmdlist **cmdlist, t_expansion *expansion)
{
	t_cmdlist	*node;
	int			i;

	i = 0;
	expansion->key = NULL;
	node = *cmdlist;
	while(node)
	{
		i = 0;
		while (node->output[i])
		{
			expansion->key = get_varkey(node->output[i]);
			if (expansion->key)
				{
					expansion->s = node->output[i];
					return (1);
				}
		}
		node = node->next;
	}
	return (0);
}
