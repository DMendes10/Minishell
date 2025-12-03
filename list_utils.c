#include "parser.h"

void	ft_lst_add_back(t_cmdlist **stack, t_cmdlist *node)
{
	t_cmdlist	*last;

	if (!stack || !node)
		return ;
	if (*stack == NULL)
		*stack = node;
	else
	{
		last = ft_lstlast(*stack);
		last->next = node;
	}
	node->next = NULL;
}
