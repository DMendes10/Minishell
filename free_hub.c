#include "minishellD.h"

void	free_master(t_master **master)
{
	if ((*master)->cmd)
		free_cmdlst((*master)->cmd);
	if ((*master)->env)
		free_envlst((*master)->env);
	if ((*master)->data)
		free ((*master)->data);
	free (*master);
	exit (1);
}

void free_envlst(t_envlst *envlst)
{
	t_envlst *ptr;

	ptr = envlst;
	while (ptr)
	{
		envlst = (envlst)->next;
		free (ptr->token);
		free (ptr->var);
		free (ptr);
		ptr = envlst;
	}
	free (envlst);
}

void free_cmdlst(t_cmdlist *cmdlst)
{
	t_cmdlist *ptr;

	ptr = cmdlst;
	while (ptr)
	{
		cmdlst = (cmdlst)->next;
		free_array (ptr->command);
		free_array (ptr->input);
		free_array (ptr->output);
		ptr = cmdlst;
	}
	free (cmdlst);
}

void exit_minishell(t_master **mstr, int exit_code)
{
	free_master(mstr);
	exit (exit_code);
}
