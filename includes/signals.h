/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncardozo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 12:00:20 by ncardozo          #+#    #+#             */
/*   Updated: 2023/12/13 11:36:29 by ncardozo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include "minishell.h"

//		 SIGNAL MODES
# define INTERACTIVE_MODE 1
# define EXECUTION_MODE 2
# define HEREDOC_MODE 3

//		 TERMIOS MODE
# define ON 1
# define OFF 0

void	set_termios(void);
void	unset_termios(void);
void	signal_mode_handling(int mode);

#endif