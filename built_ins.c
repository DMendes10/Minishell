/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diomende <diomende@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 19:13:18 by diomende          #+#    #+#             */
/*   Updated: 2025/09/23 18:23:52 by diomende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_cd(char **command)
{
	char *h_env;

	if (!command [1])
	{
		h_env = getenv ("HOME");
		if (!h_env)
			return(ft_putstr_fd ("cd: HOME not set\n", 2), 1);
		chdir (h_env);
	}
	else if (!command[2])
	{
		if (access (command[1], F_OK) != 0)
			invalid_command (command, command[1]);
		if (access (command[1], X_OK) != 0)
			no_perms_command (command, command[1]);
		else
			chdir (command[1]);
	}
	else
		return(ft_putstr_fd ("cd: too many arguments\n", 2), 1);
	return (0);
}

int ft_env(char **env)
{
	int i;

	i = 0;
	while (env[i])
	{
		ft_putstr_fd (env[i], 1);
		ft_putstr_fd ("\n", 1);
		i++;
	}
	return (1);
}

int ft_pwd()
{
	int exit_code;
	char *path;

	path = NULL;
	exit_code = 1;
	path = getcwd(NULL, 0);
	if (!path)
		printf ("%s\n", getenv ("PWD"));
	else
		printf ("%s\n", path);
	return (exit_code);
}

int ft_echo (char **command)
{
	int exit_code;
	int i;
	char *line;
		
	line = NULL;
	i = 1;
	exit_code = 1;
	if (command[1] && ft_strncmp (command[1], "-n", 100) == 0)
		i = 2;
	while (command[i])
	{
		line = ft_strjoin_gnl (line, command[i]);
		i++;
		if (command[i])
			line = ft_strjoin_gnl (line, " ");
	}
	if (command[1] && ft_strncmp (command[1], "-n", 100) == 0)
		printf ("%s",line);
	else
		printf ("%s\n", line);
	return (exit_code);
}