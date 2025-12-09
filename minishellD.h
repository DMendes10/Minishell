/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishellD.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogo <diogo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 15:04:15 by diogo             #+#    #+#             */
/*   Updated: 2025/12/09 15:04:16 by diogo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELLD_H
# define MINISHELLD_H

# include <stdio.h>
# include <unistd.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <dirent.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <linux/limits.h>
# include "src/Libft/libft.h"
# include <stdbool.h>
// # include "minishell.h"
// # include "parser.h"

// typedef struct s_envlst t_envlst;

# define SEP -1
# define EXIT_CODE 0
# define SUPER_EXIT 0
# define ECHO_FLAG 0
# define ECHO_INDEX 1
# define PATH_INDEX 0
# define ECHO_LINE 0
# define SYNTAX_ERR "syntax error near unexpected token\n"

typedef struct s_cmdlist
{
	char				**command;
	char				**input;
	char				**output;
	char				*filename;
	struct s_cmdlist	*next;
	int					hdoc_flag;
}	t_cmdlist;

typedef struct s_edata
{
	int	last_fd;
	int	fdout;
	int	fdin;
	int	pipefd[2];
	int	*pid;
	int	i;
	int	built_in_flag;
}	t_edata;

typedef struct s_envlst
{
	char			*token;
	char			*var;
	struct s_envlst	*next;
}	t_envlst;

typedef struct s_sig
{
	int	exit_code;
	int	sig_flag;
	int	fd;
	int	hdoc_flag;
}	t_sig;

typedef struct s_master
{
	t_envlst	*env;
	t_cmdlist	*cmd;
	t_edata		*data;
	int			exit;
}	t_master;

//--------------------built_ins-------------------------------------------//
//echo
int			ft_echo(char **command, int flag, int i, char *line);
int			valid_flag(char *flag);
//pwd
int			ft_pwd(t_master *mstr);
//env
int			ft_env(t_envlst *list);
//export
int			ft_export(t_master *mstr, t_cmdlist *cmdlst);
int			simple_export(t_master *mstr);
void		export_sorter(char **exp);
void		print_export(char **exp, t_master *mstr);
int			add_export(t_master *mstr, t_cmdlist *cmdlst, int super_exit);
void		exp_key(t_master *mstr, char *cmd);
void		exp_full(t_master *mstr, char *cmd);
int			change_env_var(char **cmd, t_master *mstr);
int			export_append(char **cmd, t_master *mstr);
t_envlst	*export_new_env(char **env);
int			key_check(char *key);
int			str_valid_nbr(char *str);
int			ft_strchar_int(const char *s, int c);
t_envlst	*ft_new_env_key(char *env);
t_envlst	*ft_envlstnew(char *env);
int			ft_envlst_size(t_envlst *lst);
void		ft_envlst_add_back(t_master **mstr, t_envlst *new);
char		*env_finder(t_envlst *lst, char *cmd);
//cd
int			ft_cd(char **command, t_master *mstr);
void		chdir_env_pwd(t_master *mstr, char *directory);
int			find_home(t_master *mstr);
void		update_pwd(t_master *mstr);
void		reset_oldpwd(t_master *mstr);
//unset
int			ft_unset(char **cmd, t_master *mstr);
void		delete_env_node(t_envlst *ptr, t_envlst *last, t_master **mstr);
//exit
int			ft_exit(char **cmd, t_master *mstr);
int			exit_converter(long long nbr);
bool		atoll_parser(char *str, long long *nbr);
void		exit_minishell(t_master **mstr, int exit_code);

//--------------------free_hub---------------------------------------//
void		free_array(char **s);
void		free_array(char **s);
void		free_envlst(t_envlst *envlst);
void		free_master(t_master **master);
void		free_cmdlst(t_cmdlist *cmdlst);
void		reset_master(t_master **master);

//--------------------error_handling-----------------------------------------//
void		invalid_command(t_master **mstr, char *cmd);
void		no_perms_command(t_master **mstr, char *cmd);
void		invalid_path(char *cmd);
void		no_perms_path(char *cmd);
void		alloc_error(t_master **mstr);
void		alloc_error_exit(t_master *master, char **array);
void		exec_error_handler(t_master *mstr, t_cmdlist *cmd, char *path, \
char **env);

//------------------executor------------------------------------------------//
void		executor(t_master *mstr, int cmd_count);
int			ft_wait(pid_t *pid, int cmd_count);
char		*path_finder(char **command, char **paths);
void		path_checker(t_master **mstr, char *path, t_cmdlist *cmd, int i);
void		pipe_operator(t_cmdlist *cmd, t_master *mstr);
int			exec_built(t_cmdlist *cmd, t_master *mstr);
char		**envlst_to_char(t_master *mstr);
void		built_in_single_exec(t_master *mstr, t_cmdlist *cmd);
int			is_built_in(t_cmdlist *cmd);
int			cmdlist_size(t_cmdlist *cmd);
int			pipe_operator2(t_cmdlist *cmd, t_master *mstr);
int			redir_expand_helper(t_master *mstr, char **redir, int i, int j);

//------------------redirection_hub------------------------------------------//
int			input_redirect(t_master *mstr, t_cmdlist *cmd);
int			output_redirect(t_master *mstr, t_cmdlist *cmd);
void		redir_handler(t_master *mstr, t_cmdlist *cmd);
int			built_in_redir(t_master *mstr, t_cmdlist *cmd, int saved_in, \
int saved_out);
int			h_doc_redir(t_master *mstr, t_cmdlist *cmd, int i);
int			redir_expansion(t_master *mstr, char **redir, int i);

//-----------------here-doc-------------------------------------------------//
int			hdoc_opener(t_master *mstr, t_cmdlist *cmd);
int			hdoc_rdwr(t_master *mstr, t_cmdlist *cmd, char *del);
int			hdoc_handler(t_master *mstr, t_cmdlist *cmd);
char		*hdoc_wr_helper(t_master *mstr, t_cmdlist *cmd, \
char *hdoc, char *line);
void		expand_hdoc(t_master *mstr, char **redir);
int			hdoc_signal_setup(int fd);

//-----------------iniciator-----------------------------------------------//
char		*get_input(t_master *mstr, char *prompt);
void		env_populator(t_master *mstr, char **env);
void		env_init(t_master *mstr, char **env);
void		update_shlvl(t_master *mstr);
char		**custom_env_builder(t_master *mstr);

//---------------------parsing---------------------------------------------//
int			parser(char *input, t_cmdlist **cmdlist);
void		get_varkey_cmd(t_cmdlist *node, t_master *master);
void		search_and_replace(char **s, char *key, t_master *master);
void		expansion(t_master *master);
int			check_exp(char **s, char **key, t_master *master);
void		restore_cmd(t_cmdlist *node);
void		rem_quotes(t_master *master);
void		reshaping(t_master *mstr);
void		expand_redir(t_master *mstr, char **redir);
char		*get_varkey(char *s);
int			quotes_check(char c, int quotes);

void		signals(void);
t_sig		*sign(void);
void		init_sign(void);

size_t		ft_count_words(const char *a, char c);

void		expand_redir(t_master *mstr, char **redir);
void		hdoc_del_prep(t_master *mstr);
void		remove_dollar(char **input);
void		dollar_search(t_master *mstr, int i, int j);

char		**ft_minisplit(char **a, char const *s, char c);
char		**ft_split(char const *s, char c);

#endif