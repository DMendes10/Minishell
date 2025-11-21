#include "parser.h"
#include "minishellD.h"

int	get_keysize(char *key)
{
	int	size;

	size = 0;
	while((ft_isalnum(key[size]) || key[size] == '_'))
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
			key = ft_substr(s, i + 1, get_keysize(&s[i + 1]));
			return(key);
		}
		else if (s[i] == '\'' || s[i] == '\"')
			quotes_check(s[i], quotes);
		i++;
	}
	return (key);
}

int	get_varkey_cmd(t_master *master)
{
	int		i;
	char	*key;

	i = 0;
	key = NULL;
	while(master->cmd)
	{
		i = 0;
		while (master->cmd->command && master->cmd->command[i])
		{
			key = get_varkey(master->cmd->command[i]);
			if (key)
			{
				search_and_replace(&master->cmd->command[i], key, master);
				return (1);
			}
			i++;
		}
		master->cmd = master->cmd->next;
	}
	return (0);
}

int	get_varkey_input(t_master *master, int i)
{
	char	*key;

	key = NULL;
	while(master->cmd->input[i])
	{
		i = 0;
		while (master->cmd->input && master->cmd->input[i])
		{
			if (ft_strncmp(master->cmd->input[i], "<<", 2))
				i = i + 2;
			else
			{
				key = get_varkey(master->cmd->input[i]);
				if (key)
				{
					search_and_replace(&master->cmd->input[i], key, master);
					return (1);
				}
				i++;
			}
			master->cmd = master->cmd->next;
		}
	}
	return (0);
}

int	get_varkey_output(t_master *master)
{
	int		i;
	char	*key;

	i = 0;
	key = NULL;
	while(master->cmd)
	{
		i = 0;
		while (master->cmd->output[i] && master->cmd->output[i])
		{
			key = get_varkey(master->cmd->output[i]);
			if (key)
			{
				search_and_replace(&master->cmd->output[i], key, master);
				return (1);
			}
			i++;
		}
		master->cmd = master->cmd->next;
	}
	return (0);
}
