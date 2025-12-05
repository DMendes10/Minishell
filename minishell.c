#include "minishellD.h"

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

char	*env_finder(t_envlst *lst, char *cmd)
{
	t_envlst	*ptr;

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
	t_cmdlist	*ptr;
	int			i;

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

void	initiator(int ac, char **av, char **env, t_master **mstr)
{
	(void)av;
	if (ac > 1)
		exit (1);
	master_struct_init(mstr);
	env_init(*mstr, env);
	init_sign();
	signals();
}

int	main(int ac, char **av, char **env)
{
	char		*input;
	t_master	*mstr;

	input = NULL;
	mstr = NULL;
	initiator (ac, av, env, &mstr);
	while (1)
	{
		input = get_input (mstr, "@Minishell> ");
		if (input && input[0])
		{
			if (!parser(input, &mstr->cmd))
			{
				expansion (mstr);
				reshaping(mstr);
				rem_quotes(mstr);
				executor (mstr, cmdlist_size(mstr->cmd));
			}
			reset_master (&mstr);
		}
	}
}
