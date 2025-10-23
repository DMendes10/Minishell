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
void	ft_cmd_add_back(t_cmdlist **stack, t_cmdlist *node);
t_cmdlist *new_cmd(char **cmd, int i);
t_cmdlist	*ft_lstlast(t_cmdlist *stack);
void	get_redir(char **cmd, t_cmdlist *node, int i);

#endif