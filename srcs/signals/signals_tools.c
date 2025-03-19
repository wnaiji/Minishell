/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncardozo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 17:20:54 by ncardozo          #+#    #+#             */
/*   Updated: 2023/12/13 09:04:27 by ncardozo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	set_termios(void)
{
	struct termios	sa;

	tcgetattr(STDIN_FILENO, &sa);
	sa.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &sa);
}

void	unset_termios(void)
{
	struct termios	sa;

	tcgetattr(STDIN_FILENO, &sa);
	sa.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &sa);
}
