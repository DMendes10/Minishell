#include "parser.h"
#include "minishellD.h"

int	q_check(char *c, char *s)
{
	int	i;
	int	quotes;

	i = 0;
	quotes = 0;
	while(&s[i] != c)
	{
		if(s[i] == '\'' || s[i] == '\"')
			quotes = quotes_check(s[i], quotes);
		i++;
	}
	return (quotes);
}

void	free_keyvar(char *temp, char **key, char *var)
{
	if (temp)
		free (temp);
	if (!ft_strncmp(*key, "?", 2))
		free (var);
	free (*key);
}

void	search_and_replace(char **s, char *key, t_master *master, int i, int j)
{
	int		size;
	char	*var;
	char	*temp;

	var = NULL;
	temp = NULL;
	if (!ft_strncmp(key, "?", 1))
		var = ft_itoa(master->exit);
	else
		var = env_finder(master->env, key);
	if (var)
	{
		size = ft_strlen(*s) - (ft_strlen(key)) + ft_strlen(var);
		temp = *s;
		*s = ft_calloc(size + 1, 1);
		while(temp[j] && (temp[j] != '$' || q_check(&temp[j], temp) == 1))
			(*s)[i++] = temp[j++];
		j = 0;
		while(var[j])
			(*s)[i++] = var[j++];
		j = i - ft_strlen(var) + ft_strlen(key) + 1;
		while(temp[j])
			(*s)[i++] = (temp[j++]);
	}
	free_keyvar(temp, &key, var);
}

void	expansion(t_master *master)
{
	get_varkey_cmd(master);
	// get_varkey_input(master, 0);
	// get_varkey_output(master);
	// restore_cmd(master);
}


