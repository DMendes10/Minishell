#include "minishellD.h"

int	ft_unset(char **cmd, t_envlst *lst)
{
	int i;
	t_envlst *ptr;
	t_envlst *last;

	i = 1;
	ptr = lst;
	if (!cmd[i])
		return (0);
	while (cmd[i])
	{
		while (ptr)
		{
			if (!(ft_strncmp(ptr->token, cmd[i], ft_strlen(cmd[i]) + 1)))
			{
				delete_env_node (ptr, last, &lst);
				ptr = lst;
				break;
			}
			last = ptr;
			ptr = ptr->next;
		}
		last = NULL;
		i++;
	}
	return (0);
}

void	delete_env_node(t_envlst *ptr, t_envlst *last, t_envlst **list)
{
	if (!last)
		*list = ptr->next;
	else
		last->next = ptr->next;
	free(ptr->token);
	if (ptr->var)
		free(ptr->var);
	// free(ptr->next);
	free(ptr);
}

// int	ft_exit(char **cmd, t_envlst *lst)
// {

// }