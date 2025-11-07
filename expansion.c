#include "parser.h"

int	expansion_checker(t_cmdlist *cmd, t_envlst *env)
{
	int		i;
	char	*ret;

	i = 0;
	ret = NULL;
	while (cmd)
	{
		if (ft_strnstr(cmd->command[i], env->token, ft_strlen(cmd->command[i])))
		{
			ret = ft_strdup(env->var);
			free(cmd->command[i]);
			cmd->command[i] = ret;
		}
	}
	cmd = cmd->next;
	return (1);
}

int	expansion(t_cmdlist **cmdlist, t_envlst **envlst)
{
	t_cmdlist	*cmdtable;
	t_envlst	*env;

	cmdtable = *cmdlist;
	env = *envlst;
	while(env)
	{
		while(!expansion_checker(cmdtable, env));
			env = env->next;
	}
	printf("%d", expansion_checker(cmdtable, env));
}