

#include "parser.h"

static int	redir_checker(char **cmd)
{
	if (!ft_strncmp(*cmd, "<", 2) && !ft_strncmp(*cmd, ">", 2) && !ft_strncmp(*cmd, "<<", 3) && \
		!ft_strncmp(*cmd, ">>", 3))
	{
		ft_putstr_fd("syntax error near unexpected token `>'", 2);
		return (1);
	}
	return (0);
}

static void	syntax_checker(char **cmdtable)
{
	int	i;

	i = 0;
	if (!ft_strncmp(cmdtable[i], "|", 1))
	{
		print_err("syntax error near unexpected token `|'", cmdtable);
	}
	i++;
	while (cmdtable[i])
	{
		if (!ft_strncmp(cmdtable[i], "|", 1) && !ft_strncmp(cmdtable[i - 1], "|", 1))
		{
			print_err("syntax error near unexpected token `|'", cmdtable);
		}
		else if (cmdtable[i][0] == '<' || cmdtable[i][0] == '>')
			if (redir_checker(&cmdtable[i]))
				free_args(cmdtable);
		i++;
	}
	i--;
	if (!ft_strncmp(cmdtable[i], "<", 2) || !ft_strncmp(cmdtable[i], ">", 2) || !ft_strncmp(cmdtable[i], "<<", 3) || \
		!ft_strncmp(cmdtable[i], ">>", 3) || !ft_strncmp(cmdtable[i], "|", 1))
			print_err("syntax error near unexpected token", cmdtable);
}

static void	list_creator(t_cmdlist **s_cmdlist, char **cmdtable)
{
	int	i;
	
}

static void	parser(char *input, t_cmdlist **cmdlist)
{
	char	**cmdtable;
	char	*temp;
	int		i;

	i = 0;
	temp = lexer(input);
	cmdtable = split_args(temp);
	syntax_checker(cmdtable);
	free (temp);
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
}

int main ()
{
	char *input;
	char *prompt;
	char **args;
	int	i;
	t_cmdlist	*cmdlist;
	cmdlist = NULL;
	input = NULL;
	prompt = NULL;
	args = NULL;
	i = 0;
	while(1)
	{
		i = 0;
		prompt = getcwd(NULL, 0);
		prompt = ft_strjoin_gnl (prompt, " @Minishell>$ ");
		input = get_input (prompt);
		parser(input, &cmdlist);
		if (input && input[0])
		{
			while(cmdlist)
			{	
				printf("%s\n", cmdlist->command[0]);
				printf("%s\n", cmdlist->input[1]);
				printf("%s\n", cmdlist->output[0]);
				fflush(stdout);
				cmdlist = cmdlist->next;
			}
		}
	}
}