#include "parser.h"

t_cmdlist	*ft_lstlast(t_cmdlist *stack)
{
	t_cmdlist	*ptr;

	ptr = stack;
	while (ptr->next)
		ptr = ptr->next;
	return (ptr);
}

static int	final_cmd_size(char **cmd, int i)
{
	int	count;

	count = 0;
	while(cmd[i] && cmd[i][0] != '|')
	{
		if(cmd[i][0] == '<' || cmd[i][0] == '>')
			i++;
		else
			count++;
		i++;
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
	final_cmd = ft_calloc((cmd_size + 1), sizeof(char *));
	while(cmd[i] && cmd[i][0] != '|')
	{
		if(cmd[i][0] == '<' || cmd[i][0] == '>')
			i++;
		else
			final_cmd[j++] = ft_strdup(cmd[i]);
		i++;
	}
	// final_cmd[j] = NULL;
	return(final_cmd);
}

void	ft_cmd_add_back(t_cmdlist **stack, t_cmdlist *node)
{
	t_cmdlist	*last;

	if (!stack || !node)
		return ;
	if (*stack == NULL)
		*stack = node;
	else
	{
		last = ft_lstlast(*stack);
		last->next = node;
	}
	node->next = NULL;
}

t_cmdlist *new_cmd(char **cmd, int i)
{
	t_cmdlist	*new;

	new = malloc(sizeof(t_cmdlist));
	if (!new)
		return (NULL);
	new->input = NULL;
	new->output = NULL;
	new->filename = NULL;
	new->hdoc_flag = 0;
	new->command = final_cmd(cmd, i);
	get_redir(cmd, new, i);
	new->next = NULL;
	return (new);
}

