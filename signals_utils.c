#include "minishellD.h"

t_sig	*sign(void)
{
	static t_sig	sign;

	return (&sign);
}

void	init_sign(void)
{
	sign()->exit_code = 0;
	sign()->sig_flag = 1;
}
