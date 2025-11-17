#include "minishellD.h"

int	ft_unset(char **cmd, t_master *mstr)
{
	int i;
	t_envlst *ptr;
	t_envlst *last;

	i = 1;
	ptr = mstr->env;
	// if (!cmd[i])
	// 	return (0);
	while (cmd[i])
	{
		while (ptr)
		{
			if (!(ft_strncmp(ptr->token, cmd[i], ft_strlen(cmd[i]) + 1)))
			{
				delete_env_node (ptr, last, &mstr);
				ptr = mstr->env;
				break;
			}
			last = ptr;
			ptr = ptr->next;
		}
		last = NULL;
		i++;
	}
	return (mstr->exit = 0, 0);
}

void	delete_env_node(t_envlst *ptr, t_envlst *last, t_master **mstr)
{
	if (!last)
		(*mstr)->env = ptr->next;
	else
		last->next = ptr->next;
	free(ptr->token);
	if (ptr->var)
		free(ptr->var);
	// free(ptr->next);
	free(ptr);
}

int	ft_exit(char **cmd, t_master *mstr)
{
	long long nbr;

	nbr = 0;
	if (!cmd[1])
	{
		ft_putstr_fd("exit\n", 2);
		exit_minishell (&mstr, 0);
	}
	if (atoll_parser(cmd[1], &nbr) == false)
	{
		ft_putstr_fd("exit\nexit: ", 2);
		printf ("%s: numeric argument required", cmd[1]);
		exit_minishell (&mstr, 2);
	}
	if (cmd[2])
	{
		mstr->exit = 1;
		return (ft_putstr_fd("exit\nexit: too many arguments\n", 2), 1);
	}
	ft_putstr_fd("exit\n", 2);
	exit_minishell (&mstr, exit_converter(nbr));
	return (1);
}

bool	atoll_parser(char *str, long long *nbr)
{
	int	sign;
	int	i;
	int	digit;

	i = 0;
	sign = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			sign = -1;
	}
	if (!str_valid_nbr(str + i))
		return (false);
	while (str[i])
	{
		digit = str[i++] - '0';
		if (sign == 1 && (*nbr > (LLONG_MAX - digit) / 10))
			return (false);
		if (sign == -1 && (-(*nbr) < (LLONG_MIN + digit) / 10))
			return (false);
		*nbr = *nbr * 10 + digit;
	}
	*nbr *= sign;
	return (true);
}

int	exit_converter(long long nbr)
{
	int i;

	i = 0;
	while (nbr < 0)
		nbr = nbr + 256;
	while (nbr > 0)
	{
		i++;
		nbr--;
		if (i == 256)
			i = 0;
	}
	return (i);
}
