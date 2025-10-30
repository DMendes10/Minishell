
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

int main (int ac, char **av, char **env)
{
	char *input;
	(void) av;
	input = NULL;
	t_master *mstr;

	if (ac > 1)
		exit (1);
	master_struct_init();
	if (!env_finder(env, PATH))
		env_populator(mstr, PATH, PWD, OLDPWD);
	env_populator (, env);
	while(1)
	{
		input = get_input ("@Minishel> ");
		if (input && input[0])
		{
			// parsing, trabalha Maia
			cmd_exec (input, env);
		}
	}
}
