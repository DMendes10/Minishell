
#include "minishellD.h"

// int forked_exec(char **command, char **env)
// {
// 	int		exit_code;
// 	pid_t	pid;

// 	exit_code = 1;
// 	pid = fork();
// 	if (pid == 0)
// 		child_proc(command, env);
// 	exit_code = ft_wait(pid);
// 	return (exit_code);
// }

// int	ft_wait(pid_t *pid)
// {
// 	int	status;
// 	int	exit_code;

// 	exit_code = 0;
// 	waitpid(*pid, &status, 0);
// 	if (WIFEXITED (status))
// 		exit_code = WEXITSTATUS (status);
// 	return (exit_code);
// }

void	path_checker(t_master **mstr, char *path, t_cmdlist *cmd)
{
	// char **split_cmd;

	// split_cmd = ft_split(path, ' ');
	if (!path)
		invalid_command (mstr, cmd->command[0]);
	if (access (path, F_OK) != 0)
		invalid_command (mstr, cmd->command[0]);
	if (access (path, X_OK) != 0)
		no_perms_command (mstr, cmd->command[0]);
}

char	*path_finder(char **command, char **paths)
{
	int		i;
	char	*temp;
	char	*new_path;

	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin (paths[i], "/");
		new_path = ft_strjoin (temp, command[0]);
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

void	master_struct_init(t_master **master)
{
	*master = malloc (sizeof(t_master));
	if (!*master)
	{
		perror("Mem_aloc Error: ");
		exit(1);
	}
	(*master)->data = malloc (sizeof(t_edata));
	if (!(*master)->data)
	{
		free ((*master));
		perror("Mem_aloc Error: ");
		exit (1);
	}
	(*master)->data = ft_memset ((*master)->data, 0, sizeof (t_edata));
	(*master)->cmd = NULL;
	(*master)->env = NULL;
	(*master)->exit = 0;
}

char	*env_finder(t_envlst *lst ,char *cmd)
{
	t_envlst	*ptr;
	// int	i;

	// i = 0;
	ptr = lst;
	while (ptr)
	{
		if (!ft_strncmp(ptr->token, cmd, ft_strlen(cmd) + 1))
			return (ptr->var);
		ptr = ptr->next;
	}
	return (NULL);
}

int	cmdlist_size(t_cmdlist *cmd)
{
	t_cmdlist *ptr;
	int i;

	if (!cmd)
		return (0);
	i = 0;
	ptr = cmd;
	while (ptr)
	{
		i++;
		ptr = ptr->next;
	}
	return (i);
}

int main(int ac, char **av, char **env)
{
	char *input;
	(void) av;
	t_master *mstr;
	// char	*prompt;

	input = NULL;
	mstr = NULL;
	// write (1, "a", 1);
	if (ac > 1)
		exit (1);
	master_struct_init(&mstr);
	// env_populator (mstr, env);
	env_init(mstr, env);
	while(1)
	{
		// prompt = getcwd(NULL, 0);
		input = get_input ("@Minishell> ");
		if (input && input[0])
		{
			parser(input, &mstr->cmd);
			quote_search(&mstr->cmd);
			executor (mstr, cmdlist_size(mstr->cmd));
			reset_master (&mstr);
		}
	}
}
