#include "minishellD.h"

void	exp_full(t_master *mstr ,char *cmd)
{
	t_envlst *node;
	char **splited;

	splited = malloc (3 * sizeof(char *));
	if (!splited)
		alloc_error(&mstr);
	splited[0] = ft_substr (cmd, 0, ft_strchar_int (cmd, '='));
	if (!splited[0])
		alloc_error_exit (mstr, splited);
	splited[1] = ft_strdup ((ft_strchr (cmd, '=')) + 1);
	if (!splited[1])
		alloc_error_exit(mstr, splited);
	splited[2] = NULL;
	if (change_env_var(splited, mstr) == 1)
	{
		free_array (splited);
		mstr->exit = 0;
		return;
	}
	node = export_new_env(splited);
	if (!node)
		alloc_error_exit(mstr, splited);
	ft_envlst_add_back (&mstr, node);
	mstr->exit = 0;
	free_array(splited);
}

t_envlst *export_new_env(char **env)
{
	t_envlst	*node;

	node = malloc(sizeof(t_envlst));
	if (!node)
		return (NULL);
	if (!ft_strchr (env[0], '+'))
		node->token = ft_strdup (env[0]);
	else
		node->token = ft_substr (env[0], 0, ft_strchar_int(env[0], '+'));
	if (!node->token)
		return (free (node), NULL);
	if (env[1] && env[1][0])
		node->var = ft_strdup (env[1]);
	else
		node->var = ft_strdup ("");
	if (!node->var)
		return (free (node), NULL);
	node->next = NULL;
	return (node);
}

int	change_env_var(char **cmd, t_master *mstr)
{
	t_envlst *ptr;

	ptr = mstr->env;
	if (ft_strchr (cmd[0], '+'))
		return (export_append(cmd, mstr));
	while (ptr)
	{
		if (!ft_strncmp(ptr->token, cmd[0], ft_strlen(cmd[0]) + 1))
		{
			free (ptr->var);
			ptr->var = ft_strdup(cmd[1]);
			// mstr->exit = 0;
			return (1);
		}
		ptr = ptr->next;
	}
	return (0);
}

int	export_append(char **cmd, t_master *mstr)
{
	t_envlst *ptr;

	ptr = mstr->env;
	while (ptr)
	{
		if (!ft_strncmp(ptr->token, cmd[0], ft_strchar_int (cmd[0], '+')))
		{
			ptr->var = ft_strjoin_gnl (ptr->var, cmd[1]);
			// free_array(cmd);
			mstr->exit = 0;
			return (1);
		}
		ptr = ptr->next;
	}
	return (0);
}

void	exp_key(t_master *mstr ,char *cmd)
{
	t_envlst *node;
	t_envlst *ptr;

	ptr = mstr->env;
	while (ptr)
	{
		if (!ft_strncmp(ptr->token, cmd, ft_strlen(cmd) + 1))
			return;
		ptr = ptr->next;
	}
	node = ft_new_env_key(cmd);
	// if (!node)
		// 	return_error();
	ft_envlst_add_back (&mstr, node);
}

char *key_alloc(char *key)
{
	// int i;
	char *new_key;

	// i = 0;
	if (!ft_strchr (key, '+'))
		return (ft_strdup(key));
	else
	{
		new_key = ft_substr(key, 0, ft_strchar_int (key, '+'));
		return (new_key);
	}
}

