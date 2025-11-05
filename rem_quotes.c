#include "parser.h"

int	rem_squotes(char *cmd, int quotes)
{
	int	i;

	i = 0;
	while(cmd[i])
	{
		if(cmd[i] == '\'')
		{
			if(quotes == 1)
			{
				cmd[i] = 1;
				quotes = quotes_check(cmd[i], quotes);
			}
			else if(quotes == 0)
			{
				cmd[i] = 1;
				quotes = quotes_check(cmd[i], quotes);
			}
		}
		i++;
	}
	return (quotes);
}

int	rem_dquotes(char *cmd, int quotes)
{
	int	i;

	i = 0;
	while(cmd[i])
	{
		if (cmd[i] == '\"')
		{
			if (quotes == 2)
			{
				cmd[i] = 1;
				quotes = quotes_check(cmd[i], quotes);
				expand(cmd);
			}
			if (quotes == 0)
			{
				cmd[i] = 1;
				quotes = quotes_check(cmd[i], quotes);
			}
		}
		i++;
	}
	return (quotes);
}

int	quote_rem_selector(char *cmd, int quotes)
{
	int	i;

	i = 0;
	while(cmd[i])
	{
		if(cmd[i] == '\'')
			quotes = rem_squotes(cmd, quotes);
		// else if(cmd[i] == '\"')
			// quotes = rem_dquotes(cmd, quotes);
		i++;
	}
	return(quotes);
}

void	quote_search(t_cmdlist **cmdlist)
{
	int	i;
	int j;
	int	quotes;
	t_cmdlist *node;

	i = 0;
	j = 0;
	quotes = 0;
	node = *cmdlist;
	while(node)
	{
		i = 0;
		while(node->command[i])
		{
			j = 0;
			while(node->command[i][j])
			{
				if(node->command[i][j] == '\'' ||node->command[i][j] == '\'')
					quote_rem_selector(node->command[i], quotes);
				j++;
			}
			i++;
		}
		node = node->next;
	}
}
