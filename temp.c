#include "minishellD.h"

t_cmdlist *cmd()
{
	static t_cmdlist cmd;
	
	return (&cmd);
}
