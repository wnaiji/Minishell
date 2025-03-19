/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncardozo <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 15:15:51 by ncardozo          #+#    #+#             */
/*   Updated: 2023/12/12 13:26:59 by ncardozo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//          LIBRARIES
# include "../libft/libft.h"
# include "builtins.h"
# include "ctrl_d.h"
# include "defines.h"
# include "lexer_expand.h"
# include "outputs.h"
# include "parser.h"
# include "signals.h"
# include "execution.h"
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <termios.h>
# include <term.h>

extern int	g_sig;

//           MINISHELL FUNCTIONS
void	minishell_loop(char **array);
void	prompt_back_cases(t_tools *tools);

//          FREE MEMORY FUNCTIONS
void	error_messages(t_tools *tools);
void	free_array(char **array);
void	free_struct_string(t_tools *tools);
void	handle_exit(t_tools *tools, int code);
char	*handle_memory_allocation_error(void);
void	norm_write_error(ssize_t ret);

#endif
