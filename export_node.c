#include "minishellD.h"

void	exp_full (t_envlst *lst ,char *cmd)
{
	t_envlst *node;
	char **splited;
	t_envlst *ptr;

	splited = malloc (3 * sizeof(char *));
	// if (!splited)
	// 	return_error();
	splited[0] = ft_substr (cmd, 0, ft_strchar_int (cmd, '='));
	// if (!splited[0])
	// 	return_error();
	splited[1] = ft_strdup ((ft_strchr (cmd, '=')) + 1);
	// if (!splited)
	// 	return_error();
	splited[2] = NULL;
	// splited = ft_split_pipex (cmd, '=');
	if (change_env_var(splited, lst) == 1)
		return;
	node = export_new_env(splited);
	// if (!node)
		// 	return_error();
	ft_envlst_add_back (&lst, node);
	free_array(splited);
}

t_envlst *export_new_env(char **env)
{
	t_envlst	*node;

	node = malloc(sizeof(t_envlst));
	// if (!node)
	// 	return_error(NULL);
	if (!ft_strchr (env[0], '+'))
		node->token = ft_strdup (env[0]);
	else
		node->token = ft_substr (env[0], 0, ft_strchar_int(env[0], '+'));
	if (env[1] && env[1][0])
		node->var = ft_strdup (env[1]);
	else
		node->var = ft_strdup ("");
	node->next = NULL;
	return (node);
}

int	change_env_var (char **cmd, t_envlst *lst)
{
	t_envlst *ptr;

	ptr = lst;
	if (ft_strchr (cmd[0], '+'))
		return (export_append(cmd, lst));
	while (ptr)
	{
		if (!ft_strncmp(ptr->token, cmd[0], ft_strlen(cmd[0]) + 1))
		{
			free (ptr->var);
			ptr->var = ft_strdup(cmd[1]);
			free_array(cmd);
			return (1);
		}
		ptr = ptr->next;
	}
	return (0);
}

int	export_append (char **cmd, t_envlst *lst)
{
	t_envlst *ptr;

	ptr = lst;
	while (ptr)
	{
		if (!ft_strncmp(ptr->token, cmd[0], ft_strchar_int (cmd[0], '+')))
		{
			ptr->var = ft_strjoin_gnl (ptr->var, cmd[1]);
			free_array(cmd);
			return (1);
		}
		ptr = ptr->next;
	}
	return (0);
}

void	exp_key (t_envlst *lst ,char *cmd)
{
	t_envlst *node;
	t_envlst *ptr;

	ptr = lst;
	while (ptr)
	{
		if (!ft_strncmp(ptr->token, cmd, ft_strlen(cmd) + 1))
			return;
		ptr = ptr->next;
	}
	node = ft_new_env_key(cmd);
	// if (!node)
		// 	return_error();
	ft_envlst_add_back (&lst, node);
}

t_envlst	*ft_new_env_key(char *envkey)
{
	t_envlst	*node;

	node = malloc(sizeof(t_envlst));
	if (!node)
		return (NULL);
	node->token = ft_strdup(envkey);
	node->var = NULL;
	node->next = NULL;
	return (node);
}

// char *key_alloc (char *key)
// {
// 	int i;
// 	char *new_key;

// 	i = 0;
// 	if (!ft_strchr (key, '+'))
// 		return (ft_strdup(key));
// 	else
// 	{
// 		new_key = ft_substr(key, 0, ft_strchar_int (key, '+'));
// 		return (new_key);
// 	}
// }

int key_check(char *key)
{
	int i;

	i = 1;
	if (!ft_isalpha(key[0]) && key[0] != '_')
		return (1);
	while (key[i] && key[i] != '=')
	{
		if (!ft_isalnum (key[i]) && key[0] != '_')
			break;
		i++;
	}
	if (key[i] && key[i] == '+')
	{
		if (key[i + 1] && key[i + 1] == '=')
			return (0);
	}
	else if (key[i] && key[i] == '=')
		return (0);
	else if (!key[i])
		return (0);
	return (1);
}
