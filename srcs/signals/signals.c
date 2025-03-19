/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncardozo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 11:10:52 by ncardozo          #+#    #+#             */
/*   Updated: 2023/12/13 10:50:42 by ncardozo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	handle_interactive_mode(int sig)
{
	ssize_t	ret;

	signal(sig, SIG_IGN);
	rl_on_new_line();
	rl_replace_line("", 0);
	ret = write(STDOUT_FILENO, "\n", 1);
	norm_write_error(ret);
	rl_redisplay();
	signal(sig, handle_interactive_mode);
	g_sig = 130;
}

static void	handle_sigint_execution_mode(int sig)
{
	(void)sig;
	signal(sig, handle_interactive_mode);
}

static void	handle_sigquit_execution_mode(int sig)
{
	(void)sig;
	signal(SIGQUIT, SIG_IGN);
	rl_replace_line("", 0);
	rl_redisplay();
	signal(SIGQUIT, SIG_DFL);
}

static void	handle_sigquit_heredoc_mode(int sig)
{
	(void)sig;
	signal(SIGQUIT, SIG_IGN);
	rl_replace_line("", 0);
	rl_redisplay();
	signal(SIGQUIT, SIG_DFL);
}

void	signal_mode_handling(int mode)
{
	if (mode == INTERACTIVE_MODE)
	{
		set_termios();
		signal(SIGINT, handle_interactive_mode);
		signal(SIGQUIT, SIG_IGN);
	}
	if (mode == HEREDOC_MODE)
	{
		set_termios();
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, handle_sigquit_heredoc_mode);
	}
	if (mode == EXECUTION_MODE)
	{
		unset_termios();
		signal(SIGINT, handle_sigint_execution_mode);
		signal(SIGQUIT, handle_sigquit_execution_mode);
	}
}
