
#include "minishellD.h"

void	child_process(t_master *mstr, t_cmdlist *cmd)
{
	char **paths;
	char **env;
	char *path;

	paths = NULL;
	redir_handler(mstr, cmd);
	if (!exec_built (cmd, mstr))
		exit_minishell (&mstr, mstr->exit);
	if (env_finder(mstr->env, "PATH"))
		paths = ft_split (env_finder(mstr->env, "PATH"), ':');
	path = path_finder(cmd->command, paths);
	path_checker(&mstr, path, cmd, PATH_INDEX);
	env = envlst_to_char (mstr);
	if (execve (path, cmd->command, env) == -1)
	{
		perror (cmd->command[0]);
		free_array(env);
		free_array(paths);
		exit_minishell(&mstr, errno);
	}
}

void	built_in_single_exec(t_master *mstr, t_cmdlist *cmd)
{
	int saved_stdin;
	int saved_stdout;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	dup2(mstr->data->last_fd, STDIN_FILENO);
	close (mstr->data->last_fd);
	if (built_in_redir(mstr, cmd, saved_stdin, saved_stdout))
		return;
	if (!ft_strncmp (cmd->command[0], "exit", 5))
	{
		close(saved_stdin);
		close(saved_stdout);
	}
	exec_built (cmd, mstr);
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
	mstr->data->built_in_flag = 1;
}

int	input_redirect(t_master *mstr, t_cmdlist *cmd)
{
	int i;

	i = 0;
	while (cmd->input[i])
	{
		if (!ft_strncmp (cmd->input[i], "<", 2))
		{
			mstr->data->fdin = open(cmd->input[i + 1], O_RDONLY);
			if (mstr->data->fdin < 0)
			{
				perror(cmd->input[i + 1]);
				return (1);
			}
			dup2 (mstr->data->fdin, STDIN_FILENO);
			close (mstr->data->fdin);
		}
		else if (!ft_strncmp (cmd->input[i], "<<", 2))
		{
			if (h_doc_redir (mstr, cmd, i))
				return (1);
		}
		i++;
	}
	return (0);
}

int	output_redirect(t_master *mstr, t_cmdlist *cmd)
{
	int	i;

	i = 0;
	while (cmd->output[i])
	{
		if (!ft_strncmp (cmd->output[i], ">", 2))
		{
			mstr->data->fdout = open (cmd->output[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (mstr->data->fdout == -1)
				return (perror(cmd->output[i + 1]), 1);
			dup2 (mstr->data->fdout, STDOUT_FILENO);
			close (mstr->data->fdout);
		}
		else if (!ft_strncmp (cmd->output[i], ">>", 3))
		{
			mstr->data->fdout = open (cmd->output[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (mstr->data->fdout == -1)
				return (perror(cmd->output[i + 1]), 1);
			dup2 (mstr->data->fdout, STDOUT_FILENO);
			close (mstr->data->fdout);
		}
		i++;
	}
	return (0);
}

void	pipe_operator(t_cmdlist *cmd, t_master *mstr)
{
	if (cmd->input)
		hdoc_handler(mstr, cmd);
	if (cmd->next)
	{
		if (pipe (mstr->data->pipefd) == -1)
		{
			perror("pipe: ");
			exit_minishell (&mstr, 1);
		}
	}
	if (is_built_in(cmd) && cmdlist_size(cmd) == 1)
	{
		built_in_single_exec(mstr, cmd);
		close (mstr->data->last_fd);
		return ;
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
}
