
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
	node->token = ft_substr(env, 0, ft_strchar_int (env, '=') );
	node->var = ft_substr(env, ft_strchar_int (env, '=') + 1, ft_strlen (ft_strchr (env, '=')) - 1);
	node->next = NULL;
	return (node);
}

void	ft_envlst_add_back(t_envlst **lst, t_envlst *new)
{
	t_envlst	*last;

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
		// if (!node)
		// 	return_error();
		ft_envlst_add_back (&list, node);
		i++;
	}
	return (list);
}

int	ft_envlst_size(t_envlst *lst)
{
	int i;
	t_envlst *ptr;

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

int main (int ac, char **av, char **env)
{
	int i = ac;
	char **pu = av;
	t_envlst *list;

	list = env_populator(env);
	simple_export (list);
	// while (list)
	// {
	// 	printf("%s", list->token);
	// 	printf("=");
	// 	printf("%s\n", list->var);
	// 	list = list->next;
	// }
}