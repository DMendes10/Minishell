/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogo <diogo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 15:26:27 by jomaia            #+#    #+#             */
/*   Updated: 2025/12/09 15:04:30 by diogo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "minishellD.h"

static int	redir_checker(char *cmd)
{
	if (!cmd)
		return (0);
	if (cmd[0] == '<' || cmd[0] == '>')
	{
		ft_putstr_fd(SYNTAX_ERR, 2);
		return (1);
	}
	return (0);
}

static int	syntax_checker(char **cmdtable)
{
	int	i;

	if (!*cmdtable)
		return (free_array (cmdtable), 1);
	i = 0;
	if (!ft_strncmp(cmdtable[i], "|", 1))
		return (print_err(SYNTAX_ERR, cmdtable), 1);
	while (cmdtable[i])
	{
		if (!ft_strncmp(cmdtable[i], "|", 1) && \
!ft_strncmp(cmdtable[i - 1], "|", 1))
			return (print_err(SYNTAX_ERR, cmdtable), 1);
		else if (cmdtable[i][0] == '<' || cmdtable[i][0] == '>')
		{
			if (redir_checker(cmdtable[i + 1]))
				return (free_args(cmdtable), 1);
		}
		i++;
	}
	i--;
	if (!ft_strncmp(cmdtable[i], "<", 2) || !ft_strncmp(cmdtable[i], ">", 2) \
|| !ft_strncmp(cmdtable[i], "<<", 3) || \
!ft_strncmp(cmdtable[i], ">>", 3) || !ft_strncmp(cmdtable[i], "|", 1))
		return (print_err(SYNTAX_ERR, cmdtable), 1);
	return (0);
}

int	parser(char *input, t_cmdlist **cmdlist)
{
	char	**cmdtable;
	char	*temp;
	int		i;

	i = 0;
	temp = lexer(input);
	if (!temp)
		return (ft_putstr_fd ("ERROR: unclosed quo\
tes\n", 2), sign()->exit_code = 2, free(input), 1);
	cmdtable = split_args(temp);
	free (temp);
	if (syntax_checker(cmdtable))
		return (sign()->exit_code = 2, free (input), 1);
	ft_cmd_add_back(cmdlist, new_cmd(cmdtable, i));
	while (cmdtable[i])
	{
		if (cmdtable[i][0] == '|')
		{
			i++;
			ft_cmd_add_back(cmdlist, new_cmd(cmdtable, i));
		}
		i++;
	}
	free_array(cmdtable);
	return (free (input), 0);
}
