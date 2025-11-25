
#include "minishellD.h"

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
	if (!*cmd)
		return (NULL);
	while (ptr)
	{
		if (!ft_strncmp(ptr->token, cmd, ft_strlen(cmd) + 1))
			return (ptr->var);
		ptr = ptr->next;
	}
	return ("");
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
	if (ac > 1)
		exit (1);
	master_struct_init(&mstr);
	env_init(mstr, env);
	while(1)
	{
		// prompt = getcwd(NULL, 0);
		input = get_input ("@Minishell> ");
		if (input && input[0])
		{
			parser(input, &mstr->cmd);
			// quote_search(&mstr->cmd);
			expansion(mstr);
			executor (mstr, cmdlist_size(mstr->cmd));
			reset_master (&mstr);
		}
	}
}
