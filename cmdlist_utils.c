#include "parser.h"

t_redir *get_redir(char **cmd, int i)
{
	t_redir	*ret;
	int	j;

	j = 0;
	while (cmd[i][0] != '|')
	{
		if (cmd[i][0] != '>' || cmd[i][0] != '<')
			i++;
		else
		{
			ret = malloc(sizeof(t_redir));
			if (!ret)
				return (NULL);
			ret->token[j] = ft_strdup(cmd[i]);
			ret->file[j] = ft_strdup(cmd[i + 1]);
			j++;
		}
		i++;
	}
	return (ret);
}

static int	final_cmd_size(char **cmd, int i)
{
	int	count;
	while(cmd[i][0] != '|')
	{
		if(cmd[i][0] == '<' || cmd[i][0] == '>')
			i = i + 2;
		count++;
	}
	return(count);
}

static char	**final_cmd(char **cmd, int i)
{
	char	**final_cmd;
	int		cmd_size;
	int		j;

	j = 0;
	cmd_size = final_cmd_size(cmd, i);
	cmd = malloc(cmd_size * sizeof(char *));
	while(cmd[i][0] != '|')
	{
		if(cmd[i][0] == '<' || cmd[i][0] == '>')
			i = i + 2;
		final_cmd[j++] = ft_strdup(cmd[i++]);
	}
}

t_cmdlist *new_cmd(char **cmd, int i)
{
	t_cmdlist	*new;

	new = malloc(sizeof(t_cmdlist));
	if (!new)
		return (NULL);
	new->input = get_redir(cmd, i);
	new->output = get_redir(cmd, i);
	new->command = final_cmd(cmd, i);
	new->next = NULL;
	return (new);
}

