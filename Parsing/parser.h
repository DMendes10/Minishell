/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogo <diogo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 15:26:36 by jomaia            #+#    #+#             */
/*   Updated: 2025/12/12 16:35:46 by diogo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../minishell.h"
// # include "minishell.h"
# include "../Auxiliary/Libft/libft.h"

# define SEP -1

// int		parser(t_master *mstr,char *input, t_cmdlist **cmdlist);
int			quotes_check(char c, int quotes);
void		print_err(char *error, char **arg);
void		free_args(char **args);
char		*lexer(char *input);
void		ft_cmd_add_back(t_cmdlist **stack, t_cmdlist *node);
t_cmdlist	*new_cmd(char **cmd, int i);
t_cmdlist	*ft_lstlast(t_cmdlist *stack);
void		get_redir(char **cmd, t_cmdlist *node, int i);
void		quote_search(t_cmdlist **cmdlist);
// void		expansion(t_master master);
char		**split_args(char *input);
// int			get_varkey_cmd(t_master master);
// int			get_varkey_input(t_master master, int i);
// int			get_varkey_output(t_master master);
// void		search_and_replace(char *s, char *key, t_master master);

#endif