#include "minishellD.h"

void	exp_full (t_envlst *lst ,char *cmd)
{
	t_envlst *node;
	char **splited;
	t_envlst *ptr;

	splited = ft_split_pipex (cmd, '=');
	// if (!splited)
	// 	return_error();
	ptr = lst;
	while (ptr)
	{
		if (!ft_strncmp(ptr->token, splited[0], ft_strlen(splited[0])))
		{
			free (ptr->var);
			ptr->var = ft_strdup(splited[1]);
			free_array(splited);
			return;
		}
		ptr = ptr->next;
	}
	node = ft_envlstnew(cmd);
	// if (!node)
		// 	return_error();
	ft_envlst_add_back (&lst, node);
	free_array(splited);
}

void	exp_key (t_envlst *lst ,char *cmd)
{
	t_envlst *node;
	t_envlst *ptr;

	// if (!key_check(lst, cmd))
	// 	return(printf("export: `%s': not a valid identifier", cmd));
	ptr = lst;
	while (ptr)
	{
		if (!ft_strncmp(ptr->token, cmd, ft_strlen(cmd)))
			return;
		ptr = ptr->next;
	}
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

int key_check(char *key)
{
	int i;

	i = 1;
	if (key[0] == '=')
		return (1);
	while (key[i] != '=')
	{
		if (!ft_isalnum (key[i]))
			return (1);
		i++;
	}
	return (0);
}