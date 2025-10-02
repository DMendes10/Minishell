
#include "minishellD.h"

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

void	path_checker(char *path, t_edata *data)
{
	char **split_cmd;

	split_cmd = ft_split(split_cmd, ' ');
	if (!path)
		invalid_command (split_cmd, split_cmd[0]);
	if (access (path, F_OK) != 0)
		invalid_command (split_cmd, split_cmd[0]);
	if (access (path, X_OK) != 0)
		no_perms_command (split_cmd, split_cmd[0]);
}

char	*path_finder(char *cmd, char **paths)
{
	int		i;
	char	*temp;
	char	*new_path;
	char	**split_cmd;

	i = 0;
	split_cmd = ft_split (cmd, ' ');
	while (paths[i])
	{
		temp = ft_strjoin (paths[i], "/");
		new_path = ft_strjoin (temp, split_cmd[0]);
		free (temp);
		if (access (new_path, X_OK) == 0)
		{
			free_array (paths);
			free_array (split_cmd);
			return (new_path);
		}
		free (new_path);
		i++;
	}
	free_array (split_cmd);
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
