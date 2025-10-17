#ifndef PARSER_UTILS_H
# define PARSER_UTILS_H

# include "minishell.h"
# include "src/Libft/libft.h"


# define SEP -1

char	**split_args(char *input);
int		quotes_check(char c, int quotes);
void	print_err(char *error, char **arg);
void	free_args(char **args);
char	*lexer(char *input);


#endif