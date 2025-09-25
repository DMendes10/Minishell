/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diomende <diomende@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 14:51:57 by diomende          #+#    #+#             */
/*   Updated: 2025/09/25 18:32:21 by diomende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	executor (char **commands, char **env)
{
	int	intmp;
	int	outtemp;
	int	fdin;
	int	fdout;
	int pipefd[2];
	t_cmdlst	*ptr;

	intmp = dup(0);
	outtemp = dup(1);
	ptr = cmdlst;
	while (ptr->next)
	{
		dup2 (fdin, 0);
		close (fdin);
		if (ptr->idx == 1)
		{
			if (ptr->infile)
				fdin = open (ptr->infile, O_RDONLY);
			else
				fdin = dup(intmp);
			if (!ptr->next)
			{
				pipe(pipefd);
				fdout = pipefd[1];
			}
			else
				fdout = dup(outtemp);
			if (ptr->outfile)
				fdout = open (ptr->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			dup2 (fdout, 1);
			close (fdout);
		}
		if (exec_builtin (ptr->cmd) == -1)
			forked_exec()
	}
		
	
	command = ft_split_pipex (input, ' ');
        if (ft_strncmp (command[0], "echo", 100) == 0)
            ft_echo(command);
        else if (ft_strncmp (command[0], "exit", 100) == 0)
            exit (0);
        else if (ft_strncmp (command[0], "cd", 100) == 0)
            ft_cd(command);
        else if (ft_strncmp (command[0], "pwd", 100) == 0)
            ft_pwd();
        // else if (ft_strncmp (command[0], "export", 100) == 0)
        //     ft_export();
        // else if (ft_strncmp (command[0], "unset", 100) == 0)
        //     ft_unset();
        else if (ft_strncmp (command[0], "env", 100) == 0)
            ft_env(env);
		else
			return (forked_exec (command, env));
		return (0);
}

int exec_built ()
