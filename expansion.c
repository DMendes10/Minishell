#include "parser.h"
#include "minishellD.h"


void	search_and_replace(char **s, char *key, t_master *master)
{
	int		size;
	char	*var;
	char	*temp;
	int		i;

	i = 0;
	var = env_finder(master->env, key);
	if (var)
	{
		size = ft_strlen(*s) - (ft_strlen(key)) + ft_strlen(var);
		temp = *s;
		*s = ft_calloc(size + 1, 1);
		while(temp[i] && temp[i] != '$')
			(*s)[i++] = *(temp++);
		while(*var)
			(*s)[i++] = *(var++);
		temp = temp + ft_strlen(key) + 1;
		while(*temp)
			(*s)[i++] = *(temp++);
	}
}

void	expansion(t_master *master)
{
	get_varkey_cmd(master);
}


