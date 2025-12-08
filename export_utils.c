#include "minishellD.h"

int	simple_export(t_master *mstr)
{
	char		**exp;
	int			i;
	t_envlst	*ptr;

	i = 0;
	ptr = mstr->env;
	exp = malloc(((ft_envlst_size(ptr)) + 1) * sizeof(char *));
	if (!exp)
		alloc_error (&mstr);
	while (i < ft_envlst_size(mstr->env))
	{
		exp[i] = ft_strdup(ptr->token);
		ptr = ptr->next;
		i++;
	}
	exp[i] = NULL;
	export_sorter (exp);
	print_export (exp, mstr);
	free_array (exp);
	sign()->exit_code = 0;
	return (0);
}

void	export_sorter(char **exp)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (exp[i])
	{
		j = i + 1;
		while (exp[j])
		{
			if (ft_strncmp (exp[i], exp[j], ft_strlen(exp[i]) + 1) > 0)
			{
				tmp = exp[i];
				exp[i] = exp[j];
				exp[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	print_export(char **exp, t_master *mstr)
{
	int			i;
	t_envlst	*ptr;

	i = 0;
	ptr = mstr->env;
	while (exp[i])
	{
		if (!(ft_strncmp (exp[i], ptr->token, ft_strlen(exp[i]) + 1)))
		{
			if (!ft_strncmp(ptr->token, "_", 2))
				;
			else if (ptr->var != NULL)
				printf ("declare -x %s=\"%s\"\n", ptr->token, ptr->var);
			else
				printf ("declare -x %s\n", ptr->token);
			i++;
		}
		ptr = ptr->next;
		if (!ptr)
			ptr = mstr->env;
	}
}

int	add_export(t_master *mstr, t_cmdlist *cmdlst, int super_exit)
{
	int	i;

	i = 1;
	while (cmdlst->command[i])
	{
		if (key_check(cmdlst->command[i]))
		{
			ft_putstr_fd ("export: `", 2);
			ft_putstr_fd (cmdlst->command[i], 2);
			ft_putstr_fd ("': not a valid identifier\n", 2);
			super_exit = 1;
			i++;
		}
		else
		{
			if (ft_strchar_int(cmdlst->command[i], '=') != -1)
				exp_full(mstr, cmdlst->command[i]);
			else
				exp_key (mstr, cmdlst->command[i]);
			i++;
		}
	}
	sign()->exit_code = (super_exit > 0);
	return (0);
}
