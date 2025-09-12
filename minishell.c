/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogo <diogo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:16:20 by diogo             #+#    #+#             */
/*   Updated: 2025/09/12 18:14:54 by diogo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int ft_cd(char **env)
// {
//     // int i;
//     char *h_env;

//     i = 0;
//     // while (env[i] && ft_strnstr (env[i], "HOME", 4) == NULL)
// 	// 	i++;
// 	// if (!env[i])
// 		// invalid_command (cmds, cmd);
    
//     h_env = getenv ("HOME");
//     chdir (h_env + 5);
// 	// chdir (env[i] + 5);
//     return (1);
// }

int ft_cd()
{
    // int i;
    char *h_env;

    // i = 0;
    // while (env[i] && ft_strnstr (env[i], "HOME", 4) == NULL)
	// 	i++;
	// if (!env[i])
		// invalid_command (cmds, cmd);
    
    h_env = getenv ("HOME");
    if (!h_env)
    {
        ft_putstr_fd ("cd: HOME not set\n", 2);
        return (1);
    }
    chdir (h_env);
	// chdir (env[i] + 5);
    return (1);
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

int main (int ac, char **av, char **env)
{
    char *prompt;
    char *path;
    char **command;
    (void) ac;
    (void) av;
    (void) env;
    prompt = NULL;
    path = NULL;
    command = NULL;
    while(1)
    {
        path = getcwd(NULL, 0);
        path = ft_strjoin_gnl (path, "$ ");
        prompt = readline (path);
        if (!prompt)
        {
            printf ("exit \n");
            exit (1);
        }
        command = ft_split_pipex (prompt, ' ');
        if (ft_strncmp (command[0], "echo", 100) == 0)
            ft_echo(command);
        else if (ft_strncmp (command[0], "exit", 100) == 0)
            exit (0);
        else if (ft_strncmp (command[0], "cd", 100) == 0)
            ft_cd();
        else if (ft_strncmp (command[0], "pwd", 100) == 0)
            ft_pwd();
        // else if (ft_strncmp (command[0], "export", 100) == 0)
        //     ft_export();
        // else if (ft_strncmp (command[0], "unset", 100) == 0)
        //     ft_unset();
        else if (ft_strncmp (command[0], "env", 100) == 0)
            ft_env(env);
        // printf ("%s",prompt);
    }
}
