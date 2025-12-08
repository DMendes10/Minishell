/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomaia <jomaia@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 15:27:15 by jomaia            #+#    #+#             */
/*   Updated: 2025/12/08 15:27:16 by jomaia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishellD.h"

void	signal_handler(int signal, siginfo_t *sig, void *content)
{
	(void)sig;
	(void)content;
	if (signal == SIGINT)
	{
		rl_replace_line("", 0);
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_on_new_line();
		rl_redisplay();
		sign()->sig_flag = 1;
		sign()->exit_code = 130;
	}
	if (signal == SIGQUIT)
		return ;
}

void	signal_handler_pipe(int signal, siginfo_t *sig, void *content)
{
	(void)sig;
	(void)content;
	if (signal == SIGINT)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		sign()->exit_code = 130;
	}
	if (signal == SIGQUIT)
	{
		ft_putstr_fd("Quit (core dumped)\n", STDOUT_FILENO);
		sign()->exit_code = 131;
	}
}

void	signal_handler_heredoc(int signal, siginfo_t *sig, void *content)
{
	(void)sig;
	(void)content;
	if (signal == SIGINT)
	{
		close(0);
		close(sign()->fd);
		sign()->exit_code = 130;
	}
	if (signal == SIGQUIT)
		return ;
}

void	signal_handler_here_parent(int signum)
{
	(void)signum;
	sign()->exit_code = 130;
}

void	signals(void)
{
	static struct sigaction	sig;

	sigemptyset(&sig.sa_mask);
	sig.sa_flags = SA_SIGINFO | SA_RESTART;
	sig.sa_sigaction = signal_handler;
	sigaction(SIGINT, &sig, NULL);
	if (sign()->sig_flag == 1)
		signal(SIGQUIT, SIG_IGN);
	if (sign()->sig_flag == 2)
	{
		sig.sa_sigaction = signal_handler_heredoc;
		sigaction(SIGINT, &sig, NULL);
		signal(SIGQUIT, SIG_IGN);
	}
	if (sign()->sig_flag == 3)
	{
		sig.sa_sigaction = signal_handler_pipe;
		sigaction(SIGINT, &sig, NULL);
		sigaction(SIGQUIT, &sig, NULL);
	}
	if (sign()->sig_flag == 4)
	{
		signal(SIGINT, signal_handler_here_parent);
		signal(SIGQUIT, SIG_IGN);
	}
}
