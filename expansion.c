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
	t_cmdlist	*node;

	node = master->cmd;
	while (node)
	{
		get_varkey_cmd(node, master);
		restore_cmd(node);
		node = node->next;
	}
	if (master->cmd->input)
		hdoc_del_prep(master);
	// get_varkey_input(master, 0);
	// get_varkey_output(master);
}

void	hdoc_del_prep(t_master *mstr)
{
	t_cmdlist	*node;
	int			i;
	int			j;

	i = 0;
	j = 0;
	node = mstr->cmd;
	while (node)
	{
		while (node->input[i])
		{
			j = 0;
			if (ft_strchr(node->input[i], '$'))
				dollar_search (mstr, i, j);
			i++;
		}
		node = node->next;
	}
}

void	dollar_search(t_master *mstr, int i, int j)
{
	t_cmdlist	*node;

	node = mstr->cmd;

	while (node->input[i][j])
	{
		if (node->input[i][j] == '$')
		{
			if (!ft_strncmp(node->input[i - 1], "<<", 3))
			{
				if (node->input[i][j + 1] && (node->input[i][j + 1] == '\'' || node->input[i][j + 1] == '\"'))
					remove_dollar (&node->input[i]);
			}
		}
		j++;
	}
}

void	remove_dollar(char **input)
{
	int		i;
	char	*tmp;
	char	*tmp2;
	char	*new;

	i = 0;
	i = ft_strchar_int (*input, '$');
	tmp = ft_substr (*input, 0, i);
	tmp2 = ft_substr (*input, i + 1, ft_strlen(ft_strchr(*input, '$') + 1));
	new = ft_strjoin_gnl (tmp, tmp2);
	free (*input);
	*input = new;
	free (tmp2);
}

