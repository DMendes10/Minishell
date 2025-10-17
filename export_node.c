#include "minishellD.h"

void	exp_full (t_envlst *lst ,char *cmd)
{
	t_envlst *node;

	node = ft_envlstnew(cmd);
	// if (!node)
		// 	return_error();
	ft_envlst_add_back (&lst, node);
}

void	exp_key (t_envlst *lst ,char *cmd)
{
	t_envlst *node;

	node = ft_new_env_key(cmd);
	// if (!node)
		// 	return_error();
	ft_envlst_add_back (&lst, node);
}

t_envlst	*ft_new_env_key(char *env)
{
	t_envlst	*node;

	node = malloc(sizeof(t_envlst));
	if (!node)
		return (NULL);
	node->token = ft_strdup(env);
	node->var = NULL;
	node->next = NULL;
	return (node);
}
