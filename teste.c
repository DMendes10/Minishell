#include "minishellD.h"

t_master *mstr(void)
{
	static t_master *mstr;

	return (mstr);
}