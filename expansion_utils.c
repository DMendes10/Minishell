#include "parser.h"

int	get_keysize(char *key)
{
	int	size;

	size = 0;
	if (!ft_strncmp(key, "?", 2))
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
			quotes = quotes_check(s[i], quotes);
		i++;
	}
	return (key);
}

void	get_varkey_cmd(t_master *master)
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
			while (key)
			{
				if (check_exp(&cmd->command[i], &key, master))
				{
					search_and_replace(&cmd->command[i], key, master, 0, 0);
				}
				key = get_varkey(cmd->command[i]);
			}
			i++;
		}
		cmd = cmd->next;
	}
}

void	get_varkey_input(t_master *master, int i)
{
	char	*key;
	t_cmdlist	*cmd;

	cmd = master->cmd;
	key = NULL;
	while(cmd)
	{
		i = 0;
		while (cmd->input && cmd->input[i])
		{
			if (!ft_strncmp(cmd->input[i], "<<", 3))
				i++;
			else
			{
				key = get_varkey(cmd->input[i]);
				while (key)
				{
					if (check_exp(&cmd->input[i], &key, master))
					{	

						search_and_replace(&cmd->input[i], key, master, 0, 0);
					}
					key = get_varkey(cmd->input[i]);
				}
			}
			i++;
		}
		cmd = cmd->next;
	}
}

void	get_varkey_output(t_master *master)
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
		while (cmd->output && cmd->output[i])
		{
			key = get_varkey(cmd->output[i]);
			while (key)
			{
				if (check_exp(&cmd->output[i], &key, master))
				{
					search_and_replace(&cmd->output[i], key, master, 0, 0);
				}
				key = get_varkey(cmd->output[i]);
			}
			i++;
		}
		cmd = cmd->next;
	}
}
