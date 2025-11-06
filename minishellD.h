
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
# include "src/Libft/libft.h"
# include <stdbool.h>
# include "minishell.h"
# include "parser.h"
// typedef struct s_envlst t_envlst;

# define EXIT_CODE 0
# define SUPER_EXIT 0
# define ECHO_FLAG 0
# define ECHO_INDEX 1

// typedef struct s_redir
// {
// 	char	**token;
// 	char	**file;
// }t_redir;

// typedef struct s_cmdlist
// {
// 	char				**command;
// 	char				**input;
// 	char				**output;
// 	struct s_cmdlist	*next;
// }t_cmdlist;


typedef struct s_edata
{
	int last_fd;
	int fdout;
	int fdin;
	int pipefd[2];
	int *pid;
	int i;
	int exit_code;
}t_edata;

// typedef struct s_envlst
// {
// 	char		*token;
// 	char		*var;
// 	t_envlst	*next;
// }t_envlst;

typedef struct s_master
{
	t_envlst	*env;
	t_cmdlist	*cmd;
	t_edata		*data;
	int			exit;
}t_master;


void	return_error(char *error);
char	*path_finder(char **command, char **paths);
void	free_array(char **s);
int		ft_wait(pid_t *pid, int cmd_count);
// void	close_files(int *fd, int file);
void	invalid_command(char **array, char *cmd);
void	no_perms_command(char **array, char *cmd);
int		end_quote_check(const char *s, int i);
size_t	ft_count_words_pipex(const char *a, char c, int i);
char	*ft_makestring(const char *s, char c, size_t *i);
char	*ft_makestring_quote(const char *s, size_t *i);
char	**ft_minisplit(char **a, char const *s, char c);
char	**ft_split_pipex(char const *s, char c);
int		end_quote_check(const char *s, int i);
size_t	ft_strlcpy_quotes(char *dst, const char *src, size_t size);
int 	ft_echo (char **command, int exit_code, int flag, int i);
int		ft_pwd();
int		ft_env(t_envlst *list);
int		ft_cd(char **command, t_master *mstr);
char	*get_input (char *prompt);
void	return_error(char *error);
void	invalid_command(char **array, char *cmd);
void	no_perms_command(char **array, char *cmd);
void	path_checker(char *path, t_cmdlist *cmd);
int		forked_exec (char **command, char **env);
int		simple_export(t_master *mstr);
void	export_sorter (char **exp);
void	print_export(char **exp, t_master *mstr);
int		ft_envlst_size(t_envlst *lst);
void	free_array(char **s);
int		ft_strchar_int(const char *s, int c);
int		add_export(t_master *mstr, t_cmdlist *cmdlst, int exit_code, int super_exit);
int		ft_export(t_master *mstr, t_cmdlist *cmdlst);
t_envlst	*ft_envlstnew(char *env);
t_envlst	*ft_new_env_key(char *env);
void	exp_key (t_master *mstr ,char *cmd);
void	exp_full (t_master *mstr ,char *cmd);
void	ft_envlst_add_back(t_master **mstr, t_envlst *new);
int		key_check(char *key);
char	**ft_split(char const *s, char c);
int		chdir_env_pwd(t_master *mstr, char *directory);
int		find_home(t_master *mstr);
int 	valid_flag(char *flag);
int		ft_unset(char **cmd, t_master *mstr);
void	delete_env_node(t_envlst *ptr, t_envlst *last, t_master **mstr);
int		change_env_var (char **cmd, t_master *mstr);
int		export_append (char **cmd, t_master *mstr);
t_envlst *export_new_env(char **env);
bool	atoll_parser(char *str, long long *nbr);
int		exit_converter(long long nbr);
int		str_valid_nbr (char *str);
int	ft_exit(char **cmd, t_master *mstr);
int	hdoc_rdwr(char *del);
int		hdoc_handler(t_master *mstr, t_cmdlist *cmd);
int		input_redirect (t_master *mstr, t_cmdlist *cmd);
void	env_populator (t_master *mstr, char **env);
int		str_valid_nbr (char *str);
void	free_envlst (t_envlst *envlst);
void	free_master(t_master **master);
void	pipe_operator(t_cmdlist *cmd, t_master *mstr);
char	*env_finder (t_envlst *lst ,char *cmd);
int		exec_built (t_cmdlist *cmd, t_master *mstr);
void	exit_minishell(t_master **mstr, int exit_code);
int		executor(t_master *mstr, int cmd_count);
void	parser(char *input, t_cmdlist **cmdlist);
void	invalid_path(char **array, char *cmd);
void	no_perms_command(char **array, char *cmd);
void	no_perms_path(char **array, char *cmd);
void	output_redirect(t_master *mstr, t_cmdlist *cmd);
char	**envlst_to_char(t_master *mstr);
void free_cmdlst(t_cmdlist *cmdlst);
int	is_built_in(t_cmdlist *cmd);
int	cmdlist_size(t_cmdlist *cmd);
void	built_in_single_exec(t_master *mstr, t_cmdlist *cmd);


#endif