/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-maia <joao-maia@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 16:10:01 by diogo             #+#    #+#             */
/*   Updated: 2025/09/25 16:09:13 by joao-maia        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <dirent.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "src/Libft/libft.h"

typedef struct s_cmdlist
{
	char				*command;
	char				*input;
	char				*output;
    struct s_command	*next;
}t_cmdlist;

typedef struct s_data
{
	int ac;
	char **av;
	char **env;
    t_commands commands;
}t_data;

void	return_error(char *error);
void	child_proc1(char **av, char *envp[], int pipefd[]);
void	child_proc2(char **av, char *envp[], int pipefd[]);
void	exec_cmd(char *av, char *envp[]);
char	*path_finder(char *cmd, char *envp[], char **cmds);
char	*path_check(char *cmd, char **paths);
void	free_array(char **s);
int		ft_wait(pid_t pid);
void	close_files(int *fd, int file);
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
int		ft_echo (char **command);
int		ft_pwd();
int		ft_env(char **env);
int		ft_cd (char **command);
char	*get_input (char *prompt);
int		cmd_exec (char *input, char **env);
void	return_error(char *error);
void	invalid_command(char **array, char *cmd);
void	no_perms_command(char **array, char *cmd);
char	*path_check(char *cmd, char **paths);
char	*path_finder(char *cmd, char **env, char **cmds);
void	child_proc(char **command, char **env);
int		forked_exec (char **command, char **env);

#endif