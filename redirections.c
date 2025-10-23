#include "parser.h"

void	count_redir(char **cmd, int *n_input, int *n_output, int i)
{
	while (cmd[i] && cmd[i][0] != '|')
	{
		if (cmd[i][0] == '>')
			(*n_output)++;
		else if (cmd[i][0] == '<')
			(*n_input)++;
		i++;
	}
}

void	populate_input(char **cmd, t_cmdlist *node, int i)
{
	int	j;

	j  = 0;
	while (cmd[i] && cmd[i][0] != '|')
	{
		if (cmd[i][0] == '<')
		{
			node->input[j++] = ft_strdup(cmd[i++]);
			node->input[j++] = ft_strdup(cmd[i++]);
		}
		else
			i++;
	}
}

void	populate_output(char **cmd, t_cmdlist *node, int i)
{
	int	j;

	j  = 0;
	while (cmd[i] && cmd[i][0] != '|')
	{
		if (cmd[i][0] == '>')
		{
			node->output[j++] = ft_strdup(cmd[i++]);
			node->output[j++] = ft_strdup(cmd[i++]);
		}
		else
			i++;
	}
}

void	get_redir(char **cmd, t_cmdlist *node, int i)
{
	int	n_input;
	int	n_output;

	n_input = 0;
	n_output = 0;
	count_redir(cmd, &n_input, &n_output, i);
	if(n_input)
	{
		node->input = malloc((n_input * 2 + 1) * sizeof(char *));
		if(!node->input)
			return ;
		populate_input(cmd, node, i);
	}
	write(1, "Test4", 5);
	if(n_output)
	{
		node->output = malloc((n_output * 2 + 1) * sizeof(char *));
		if(!node->output)
			return ; 
		populate_output(cmd, node , i);
	}
	write(1, "Test5", 5);
}
