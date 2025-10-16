

#include "parser.h"

static int	redir_checker(char **cmd)
{
	if (!ft_strncmp(*cmd, "<", 2) || !ft_strncmp(*cmd, ">", 2) || !ft_strncmp(*cmd, "<<", 3) || \
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

static char	**parser(char *input)
{
	char	**cmdtable;
	char	*temp;
	int		i;

	i = 0;
	temp = lexer(input);
	cmdtable = split_args(temp);
	syntax_checker(cmdtable);
	free (temp);
	return(cmdtable);
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
		if (input && input[0])
		{
			args = parser(input);
			while(args[i])
			{	
				printf("%s\n", args[i++]);
				fflush(stdout);
			}
			printf("%d", i);
		}
	}
}