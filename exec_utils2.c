#include "minishellD.h"

void	child_process(t_master *mstr, t_cmdlist *cmd)
{
	char	**paths;
	char	**env;
	char	*path;

	paths = NULL;
	sign()->sig_flag = 3;
	signals();
	redir_handler(mstr, cmd);
	if (cmd->command[0] && !*cmd->command[0])
		invalid_command (&mstr, cmd->command[0]);
	if (!exec_built (cmd, mstr))
		exit_minishell (&mstr, sign()->exit_code);
	if (env_finder(mstr->env, "PATH"))
		paths = ft_split (env_finder(mstr->env, "PATH"), ':');
	path = path_finder(cmd->command, paths);
	path_checker(&mstr, path, cmd, PATH_INDEX);
	env = envlst_to_char (mstr);
	if (execve (path, cmd->command, env) == -1)
	{
		exec_error_handler (mstr, cmd, path, env);
	}
}

void	built_in_single_exec(t_master *mstr, t_cmdlist *cmd)
{
	int	saved_stdin;
	int	saved_stdout;

	mstr->data->built_in_flag = 1;
	saved_stdin = dup (STDIN_FILENO);
	saved_stdout = dup (STDOUT_FILENO);
	dup2 (mstr->data->last_fd, STDIN_FILENO);
	close (mstr->data->last_fd);
	if (built_in_redir (mstr, cmd, saved_stdin, saved_stdout))
		return ;
	if (!ft_strncmp (cmd->command[0], "exit", 5))
	{
		close (saved_stdin);
		close (saved_stdout);
	}
	exec_built (cmd, mstr);
	dup2 (saved_stdin, STDIN_FILENO);
	dup2 (saved_stdout, STDOUT_FILENO);
	close (saved_stdin);
	close (saved_stdout);
}

size_t	ft_count_words(const char *a, char c)
{
	size_t	i;
	size_t	count;

	count = 0;
	i = 0;
	while (a[i])
	{
		while (a[i] == c)
			i++;
		if (a[i])
			count++;
		while (a[i] && a[i] != c)
			i++;
	}
	return (count);
}

void	pipe_operator(t_cmdlist *cmd, t_master *mstr)
{
	if (cmd->input)
	{
		if (hdoc_handler(mstr, cmd))
		{
			if (cmd->next && sign()->hdoc_flag == 1)
			{
				pipe (mstr->data->pipefd);
				close (mstr->data->pipefd[1]);
				dup2 (mstr->data->pipefd[0], mstr->data->last_fd);
				close (mstr->data->pipefd[0]);
				sign()->hdoc_flag = 0;
				return ;
			}
			dup2 (mstr->data->last_fd, STDIN_FILENO);
			return ;
		}
	}
	if (cmd->next)
	{
		if (pipe (mstr->data->pipefd) == -1)
			exit_minishell (&mstr, 1);
	}
	if (pipe_operator2 (cmd, mstr))
		return ;
}

int	pipe_operator2(t_cmdlist *cmd, t_master *mstr)
{
	if (is_built_in(cmd) && cmdlist_size(mstr->cmd) == 1)
	{
		built_in_single_exec(mstr, cmd);
		close (mstr->data->last_fd);
		return (1);
	}
	mstr->data->pid[mstr->data->i] = fork();
	if (mstr->data->pid[mstr->data->i] == 0)
		child_process (mstr, cmd);
	close (mstr->data->last_fd);
	if (cmd->next)
	{
		close (mstr->data->pipefd[1]);
		mstr->data->last_fd = mstr->data->pipefd[0];
	}
	return (0);
}
