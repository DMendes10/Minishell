#include "parser.h"
#include "minishellD.h"

int	check_exp(char **s, char **key, t_master *master)
{
	char	*var;
	int		i;

	i = 0;
	var = NULL;
	if (!ft_strncmp(*key, "?", 2))
		var = ft_itoa(master->exit);
	else
		var = env_finder(master->env, *key);
	if (var)
	{
		if (!ft_strncmp(*key, "?", 2))
			free (var);
		return (1);
	}
	else
	{
		while((*s)[i] && (*s)[i] != '$')
			i++;
		if ((*s)[i] && (*s)[i] == '$')
			(*s)[i]= -1;
		free (*key);
		return (0);
	}
}

void	restore_cmd(t_master *master)
{
	int		i;
	int		j;
	t_cmdlist	*cmd;

	cmd = master->cmd;
	i = 0;
	j = 0;
	while(cmd)
	{
		i = 0;
		while (cmd->command && cmd->command[i])
		{
			j = 0;
			while(cmd->command[i][j])
			{
				if (cmd->command[i][j] == -1)
					cmd->command[i][j] = '$';
				j++;
			}
			i++;
		}
		cmd = cmd->next;
	}
}

