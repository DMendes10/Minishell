
#include "minishell.h"

char *get_input (char *prompt)
{
	char *input;
	input = readline (prompt);
	if (input && input[0])
		add_history (input);
	else if (!input)
		exit (1);
	return (input);
}

int forked_exec (char **command, char **env)
{
	int		exit_code;
	pid_t	pid;

	exit_code = 1;
	pid = fork();
	if (pid == 0)
		child_proc(command, env);
	exit_code = ft_wait(pid);
	return (exit_code);
}

int	ft_wait(pid_t pid)
{
	int	status;
	int	exit_code;

	exit_code = 0;
	waitpid(pid, &status, 0);
	if (WIFEXITED (status))
		exit_code = WEXITSTATUS (status);
	return (exit_code);
}

void	child_proc(char **command, char **env)
{
	char	*path;

	path = path_finder(command[0], env, command);
	if (!path)
		invalid_command (command, command[0]);
	if (access (path, F_OK) != 0)
		invalid_command (command, command[0]);
	if (access (path, X_OK) != 0)
		no_perms_command (command, command[0]);
	if (execve(path, command, env) == -1)
	{
		free_array (command);
		return_error(command[0]);
	}
}

char	*path_finder(char *cmd, char **env, char **cmds)
{
	char	**paths;
	int		i;

	i = 0;
	if (ft_strchr (cmd, '/') != NULL)
		return (cmd);
	if (!env[0])
		invalid_command (cmds, cmd);
	while (env[i] && ft_strnstr (env[i], "PATH", 4) == NULL)
		i++;
	if (!env[i])
		invalid_command (cmds, cmd);
	paths = ft_split (env[i] + 5, ':');
	return (path_check (cmd, paths));
}

char	*path_check(char *cmd, char **paths)
{
	int		i;
	char	*temp;
	char	*new_path;

	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin (paths[i], "/");
		new_path = ft_strjoin (temp, cmd);
		free (temp);
		if (access (new_path, X_OK) == 0)
		{
			free_array (paths);
			return (new_path);
		}
		free (new_path);
		i++;
	}
	free_array (paths);
	return (NULL);
}

int	cmd_exec (char *input, char **env)
{
	char **command;
	
	command = ft_split_pipex (input, ' ');
        if (ft_strncmp (command[0], "echo", 100) == 0)
            ft_echo(command);
        else if (ft_strncmp (command[0], "exit", 100) == 0)
            exit (0);
        else if (ft_strncmp (command[0], "cd", 100) == 0)
            ft_cd(command);
        else if (ft_strncmp (command[0], "pwd", 100) == 0)
            ft_pwd();
        // else if (ft_strncmp (command[0], "export", 100) == 0)
        //     ft_export();
        // else if (ft_strncmp (command[0], "unset", 100) == 0)
        //     ft_unset();
        else if (ft_strncmp (command[0], "env", 100) == 0)
            ft_env(env);
		else
			return (forked_exec (command, env));
		return (0);
}

int main (int ac, char **av, char **env)
{
	char *input;
	char *prompt;
	char **command;
	(void) ac;
	(void) av;
	input = NULL;
	prompt = NULL;
	command = NULL;
	while(1)
	{
		prompt = getcwd(NULL, 0);
		prompt = ft_strjoin_gnl (prompt, " @Minishell>$ ");
		input = get_input (prompt);
		if (input && input[0])
		{
			// parsing, trabalha Maia
			cmd_exec (input, env);
		}
	}
}
