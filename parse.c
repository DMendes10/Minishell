

#include "parser.h"

static int	parser(char *input)
{
	char		**temp;

	int	i;
	i = 0;

	temp = split_args(input);

}

int main ()
{
	char *input;
	char *prompt;
	char **args;
	int	i;
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
			args = split_args(input);
			while(args[i])
			{	
				printf("%s\n", args[i++]);
				fflush(stdout);
		}
		}
	}
	while(args[i])
	{	
		printf("%s\n", args[i++]);
		fflush(stdout);
	}
}