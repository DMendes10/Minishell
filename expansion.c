#include "parser.h"
#include "minishellD.h"

void	search_and_replace(char *s, char *key, t_envlst **env)
{
	int			size;
	char		*var;
	char		*temp;
	t_envlst	*node;

	var = env_finder(node, key);
	node = *env;
	if (var)
	{
		size = ft_strlen(s) - ft_strlen(key) + ft_strlen(var);
		temp = s;
		s = ft_calloc(size + 1, 1);
		while(temp && *temp != '$')
			*(s++) = *(temp++);
		while(var)
			*(s++) = *(var++);
		temp = temp + ft_strlen(key);
		while(temp)
			*(s++) = *(temp++);
		free (temp);
	}
}

void	expansion(t_cmdlist **cmdlist, t_envlst **env)
{
	t_expansion	*exp;

	exp = malloc(sizeof(t_expansion));
	while(get_varkey_cmd(cmdlist, exp))
		search_and_replace(exp->s, exp->key, env);
	while(get_varkey_input(cmdlist, exp, 0))
		search_and_replace(exp->s, exp->key, env);
	while(get_varkey_output(cmdlist, exp))
		search_and_replace(exp->s, exp->key, env);

}


