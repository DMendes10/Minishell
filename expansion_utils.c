#include "parser.h"

int	get_keysize(char *key)
{
	int	size;

	size = 0;
	if (!ft_strncmp(key, "?", ft_strlen(key)))
		size = 1;
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
	t_cmdlist	*cmd;

	cmd = master->cmd;
	i = 0;
	key = NULL;
	while(cmd)
	{
		i = 0;
		while (cmd->command && cmd->command[i])
		{
			key = get_varkey(cmd->command[i]);
			if (key)
			{
				search_and_replace(&cmd->command[i], key, master, 0, 0);
				return (1);
			}
			i++;
		}
		cmd = cmd->next;
	}
	return (0);
}

int	get_varkey_input(t_master *master, int i)
{
	char	*key;
	t_cmdlist	*cmd;

	cmd = master->cmd;
	key = NULL;
	while(master->cmd->input[i])
	{
		i = 0;
		while (cmd->input && cmd->input[i])
		{
			if (ft_strncmp(cmd->input[i], "<<", 2))
				i = i + 2;
			else
			{
				key = get_varkey(cmd->input[i]);
				if (key)
				{
					search_and_replace(&cmd->input[i], key, master, 0, 0);
					return (1);
				}
				i++;
			}
			cmd = cmd->next;
		}
	}
	return (0);
}

int	get_varkey_output(t_master *master)
{
	int		i;
	char	*key;
	t_cmdlist	*cmd;

	cmd = master->cmd;
	i = 0;
	key = NULL;
	while(cmd)
	{
		i = 0;
		while (cmd->output[i] && cmd->output[i])
		{
			key = get_varkey(cmd->output[i]);
			if (key)
			{
				search_and_replace(&cmd->output[i], key, master, 0, 0);
				return (1);
			}
			i++;
		}
		cmd = cmd->next;
	}
	return (0);
}
