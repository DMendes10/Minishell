#include "parser.h"

t_redir *get_redir(char **cmd, int i)
{
	t_redir	*ret;

	while (cmd[i][0] != '|')
	{
		if (cmd[i][0] != '>' || cmd[i][0] != '<')
			i++;
		else
		{
			ret = malloc(sizeof(t_redir));
			if (!ret)
				return (NULL);
			ret->token = ft_strdup(cmd[i]);
			ret->file = ft_strdup(cmd[i + 1]);
		}
	}
	return (NULL);
}

static char	*rem_redir(char **cmd)
{
	
}

t_cmdlist *new_cmd(char **cmd, int i)
{
	t_cmdlist	*new;

	new = malloc(sizeof(t_cmdlist));
	if (!new)
		return (NULL);
	new->command = cmd;
	new->input = NULL;
	new->output = NULL;
	new->next = NULL;
	return (new);
}

