#include "minishellD.h"

int	simple_export(t_envlst *lst)
{
	char **exp;
	int i;
	t_envlst *ptr;

	i = 0;
	ptr = lst;
	exp = malloc (((ft_envlst_size(lst)) + 1) * sizeof(char*));
	// if (!exp)
	// 	return_error();
	while (i < ft_envlst_size(lst))
	{
		exp[i] = ft_strdup(ptr->token);
		ptr = ptr->next;
		i++;
	}
	exp[i] = NULL;
	export_sorter (exp);
	print_export (exp, lst);
	free_array (exp);
	return (0);
}

void	export_sorter (char **exp)
{
	int i;
	int j;
	char *tmp;

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

void	print_export(char **exp, t_envlst *lst)
{
	int			i;
	t_envlst	*ptr;

	i = 0;
	ptr = lst;
	while (exp[i])
	{
		if (ft_strncmp (exp[i], ptr->token, ft_strlen(exp[i]) + 1) == 0)
		{
			if (ptr->var != NULL)
				printf("declare -x %s=\"%s\"\n",ptr->token ,ptr->var);
			else
				printf("declare -x %s\n",ptr->token);
			// ptr = lst;
			i++;
		}
		ptr = ptr->next;
		if (!ptr)
			ptr = lst;
	}
}

int	add_export(t_envlst *lst, t_cmdlist *cmdlst, int exit_code, int super_exit)
{
	int i;

	i = 1;
	while (cmdlst->command[i])
	{
		if (key_check(cmdlst->command[i]))
		{
			printf("export: `%s': not a valid identifier\n", cmdlst->command[i]);
			super_exit = 1;
			i++;
		}
		else
		{
			if (ft_strchar_int(cmdlst->command[i], '=') != -1)
				exp_full(lst, cmdlst->command[i]);
			else
				exp_key (lst, cmdlst->command[i]);
			i++;
		}
	}
	return (super_exit > exit_code);
}
