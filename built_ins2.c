/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diomende <diomende@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 15:01:54 by diogo             #+#    #+#             */
/*   Updated: 2025/12/11 13:10:10 by diomende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishellD.h"

int	ft_unset(char **cmd, t_master *mstr)
{
	int			i;
	t_envlst	*ptr;
	t_envlst	*last;

	i = 1;
	ptr = mstr->env;
	last = ptr;
	while (cmd[i])
	{
		while (ptr)
		{
			if (!(ft_strncmp(ptr->token, cmd[i], ft_strlen(cmd[i]) + 1)))
			{
				delete_env_node (ptr, last, &mstr);
				ptr = mstr->env;
				break ;
			}
			last = ptr;
			ptr = ptr->next;
		}
		last = NULL;
		i++;
	}
	return (sign()->exit_code = 0, 0);
}

int	ft_exit(char **cmd, t_master *mstr)
{
	long long	nbr;

	nbr = 0;
	if (!cmd[1])
	{
		ft_putstr_fd("exit\n", 1);
		exit_minishell (&mstr, sign()->exit_code);
	}
	if (atoll_parser(cmd[1], &nbr) == false)
	{
		ft_putstr_fd("exit\nexit: ", 1);
		ft_putstr_fd(cmd[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit_minishell (&mstr, 2);
	}
	if (cmd[2])
	{
		if (sign()->exit_code < 1)
			sign()->exit_code = 1;
		ft_putstr_fd("exit\n", 1);
		return (ft_putstr_fd("exit: too many arguments\n", 2), 1);
	}
	ft_putstr_fd("exit\n", 1);
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
	return ((int)(unsigned char)nbr);
}
