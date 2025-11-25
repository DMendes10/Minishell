#include "parser.h"

static int	redir_checker(char *cmd)
{
	if(!cmd)
		return (0);
	if (!ft_strncmp(cmd, "<", 2) && !ft_strncmp(cmd, ">", 2) && !ft_strncmp(cmd, "<<", 3) && \
		!ft_strncmp(cmd, ">>", 3))
	{
		ft_putstr_fd("syntax error near unexpected token `>'\n", 2);
		return (1);
	}
	return (0);
}

static int	syntax_checker(char **cmdtable)
{
	int	i;

	i = 0;
	if (!ft_strncmp(cmdtable[i], "|", 1))
		return(print_err("syntax error near unexpected token `|'\n", cmdtable), 1);
	while (cmdtable[i])
	{
		if (!ft_strncmp(cmdtable[i], "|", 1) && !ft_strncmp(cmdtable[i - 1], "|", 1))
			return(print_err("syntax error near unexpected token `|'\n", cmdtable), 1);
		else if (cmdtable[i][0] == '<' || cmdtable[i][0] == '>')
		{
			if (redir_checker(cmdtable[i + 1]))
				return(free_args(cmdtable), 1);
		}
		i++;
	}
	i--;
	if (!ft_strncmp(cmdtable[i], "<", 2) || !ft_strncmp(cmdtable[i], ">", 2) || !ft_strncmp(cmdtable[i], "<<", 3) || \
		!ft_strncmp(cmdtable[i], ">>", 3) || !ft_strncmp(cmdtable[i], "|", 1))
			return(print_err("syntax error near unexpected token\n", cmdtable), 1);
	return (0);
}

int	parser(t_master *mstr, char *input, t_cmdlist **cmdlist)
{
	char	**cmdtable;
	char	*temp;
	int		i;

	i = 0;
	temp = lexer(input);
	if (!temp)
		return (ft_putstr_fd ("ERROR: unclosed quotes found\n", 2), free(input), 1);
	cmdtable = split_args(temp);
	free (temp);
	if (syntax_checker(cmdtable))
		return(mstr->exit = 2, free (input), 1);
	ft_cmd_add_back(cmdlist, new_cmd(cmdtable, i));
	while (cmdtable[i])
	{
		if (cmdtable[i][0] == '|')
		{
			i++;
			ft_cmd_add_back(cmdlist, new_cmd(cmdtable, i));
		}
		i++;
	}
	free_array(cmdtable);
	free (input);
	return (0);
}

// int main ()
// {
// 	char *input;
// 	char *prompt;
// 	char **args;
// 	int	i, j;
// 	t_cmdlist	*cmdlist;
// 	cmdlist = NULL;
// 	input = NULL;
// 	prompt = NULL;
// 	args = NULL;
// 	i = 0;
// 	j = 0;
// 	while(1)
// 	{
// 		i = 0;
// 		prompt = getcwd(NULL, 0);
// 		prompt = ft_strjoin_gnl (prompt, " @Minishell>$ ");
// 		input = get_input (prompt);
// 		parser(input, &cmdlist);
// 		quote_search(&cmdlist);
// 		if (input && input[0])
// 		{
// 			j = 0;
// 			while(cmdlist)
// 			{	
// 				i = 0;
// 				while(cmdlist->command[i])
// 					printf("Command[%d]:%s\n", j, cmdlist->command[i++]);
// 				i = 0;
// 				if(cmdlist->input)
// 				{
// 					while(cmdlist->input[i])
// 						printf("Input[%d]:%s\n", j, cmdlist->input[i++]);
// 				}
// 				i = 0;
// 				if(cmdlist->output)
// 				{
// 					while(cmdlist->output[i])
// 						printf("Output[%d]:%s\n", j, cmdlist->output[i++]);
// 				}
// 				cmdlist = cmdlist->next;
// 				j++;
// 			}
// 		}
// 	}
// }