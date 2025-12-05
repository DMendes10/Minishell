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
	node->token = ft_substr (env, 0, ft_strchar_int (env, '='));
	node->var = ft_substr (env, ft_strchar_int (env, '=') + 1, ft_strlen
			(ft_strchr (env, '=')) - 1);
	node->next = NULL;
	return (node);
}

void	ft_envlst_add_back(t_master **mstr, t_envlst *new)
{
	t_envlst	*last;

	if (!new || !mstr)
		return ;
	last = (*mstr)->env;
	if (!(*mstr)->env)
	{
		(*mstr)->env = new;
		return ;
	}
	else
	{
		while (last->next != NULL)
			last = last->next;
		last->next = new;
	}
}

void	env_populator(t_master *mstr, char **env)
{
	int			i;
	t_envlst	*node;

	node = NULL;
	i = 0;
	while (env[i])
	{
		node = ft_envlstnew (env[i]);
		if (!node)
			alloc_error (&mstr);
		ft_envlst_add_back (&mstr, node);
		i++;
	}
	return ;
}

int	ft_envlst_size(t_envlst *lst)
{
	int			i;
	t_envlst	*ptr;

	i = 0;
	if (!lst)
		return (0);
	ptr = lst;
	while (ptr)
	{
		ptr = ptr->next;
		i++;
	}
	return (i);
}
