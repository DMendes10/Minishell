#include "minishell.h"
#include "parser.h"

void	free_args(char **args)
{
	int	i;
	
	i = 0;
	while(args[i])
		free(args[i++]);
	free(args);
}

void	print_err(char *error, char **arg)
{
	//free_args(arg);
	ft_putstr_fd(error, 2);
}

