#include "minishellD.h"

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

int str_valid_nbr (char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (!ft_isdigit(str[i]))
            return (0);
        i++;
    }
    return (1);
}
