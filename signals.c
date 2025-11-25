#include "minishellD.h"
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

volatile sig_atomic_t g_heredoc_interrupted = 0;

static void sigint_parent(int signo)
{
    (void)signo;
    write(1, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

static void sigint_heredoc(int signo)
{
    (void)signo;
    g_heredoc_interrupted = 1;
    write(1, "\n", 1);
}

/* for main shell prompt */
void set_parent_signals(void)
{
    signal(SIGINT, sigint_parent); /* Ctrl-C: do not kill shell, redraw prompt */
    signal(SIGQUIT, SIG_IGN);      /* Ctrl-\ ignored in prompt */
}

/* for forked child processes before execve */
void set_child_signals(void)
{
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
}

/* for heredoc reading */
void set_heredoc_signals(void)
{
    g_heredoc_interrupted = 0;
    signal(SIGINT, sigint_heredoc);
    signal(SIGQUIT, SIG_IGN);
}

/* restore defaults (if needed) */
void reset_signals(void)
{
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
}