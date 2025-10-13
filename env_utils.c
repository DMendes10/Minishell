
#include "minishellD.h"

int	ft_strchar_int(const char *s, int c)
{
	size_t	i;
	char	*s1;

	i = 0;
	s1 = (char *)s;
	while (s1[i])
	{
		if (s1[i] == (char)c)
			return (i);
		i++;
	}
	if ((char)c == '\0')
		return (i);
	return (-1);
}

t_envlst	*ft_envlstnew(char *env)
{
	t_envlst	*node;

	node = malloc(sizeof(t_envlst));
	if (!node)
		return (NULL);
	node->token = ft_substr(env, 0, ft_strchar_int (env, '=') - 1);
	node->var = ft_substr(env, ft_strchar_int (env, '=') + 1, ft_strlen (ft_strchr (env, '=')) - 1);
	node->next = NULL;
	return (node);
}

void	ft_envlst_add_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (!new || !lst)
		return ;
	last = *lst;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	else
	{
		while (last->next != NULL)
			last = last->next;
		last->next = new;
	}
}

t_envlst	*env_populator (char **env)
{
	int i;
	t_envlst *list;
	t_envlst *node;

	list = NULL;
	node = NULL;
	i = 0;
	while (env[i])
	{
		node = ft_envlstnew(env[i]);
		ft_envlst_add_back (&list, node);
		i++;
	}
	return (list);
}
