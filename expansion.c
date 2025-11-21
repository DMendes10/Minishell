#include "parser.h"
#include "minishellD.h"

void	free_keyvar(char *temp, char *key, char *var)
{
	free (temp);
	if (!ft_strncmp(key, "?", 2))
		free (var);
	free (key);
}

void	search_and_replace(char **s, char *key, t_master *master, int i, int j)
{
	int		size;
	char	*var;
	char	*temp;

	var = NULL;
	if (!ft_strncmp(key, "?", 2))
		var = ft_itoa(master->exit);
	else
		var = env_finder(master->env, key);
	if (var)
	{
		size = ft_strlen(*s) - (ft_strlen(key)) + ft_strlen(var);
		temp = *s;
		*s = ft_calloc(size + 1, 1);
		while(temp[j] && temp[j] != '$')	
			(*s)[i++] = temp[j++];
		j = 0;
		while(var[j])
			(*s)[i++] = var[j++];
		j = i - ft_strlen(var) + ft_strlen(key) + 1;
		while(temp[j])
			(*s)[i++] = (temp[j++]);
		free_keyvar(temp, key, var);
	}
	free (key);
}

void	expansion(t_master *master)
{
	get_varkey_cmd(master);
}


