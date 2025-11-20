#include "minishellD.h"

void	alloc_error(t_master **mstr)
{
	perror("ERROR");
	exit_minishell (mstr, 1);
}

void	alloc_error_exit(t_master *master, char **array)
{
	free_array (array);
	alloc_error (&master);
}
