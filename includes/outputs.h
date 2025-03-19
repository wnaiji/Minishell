/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outputs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walidnaiji <walidnaiji@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 07:54:34 by ncardozo          #+#    #+#             */
/*   Updated: 2023/12/04 18:46:15 by walidnaiji       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OUTPUTS_H
# define OUTPUTS_H
# include "minishell.h"

# define MINISHELL_PROMPT2 "\033[1;36mcarnashell\033[1;31m$> \033[0m"
# define MINISHELL_PROMPT1 "\033[1;36mcarnashell\033[1;32m$> \033[0m"

# define PROMPT "carnashell"
# define SIGN "$> "

//          ANSI COLORS
# define B_C "\001\033[1;36m\002"
# define V_C "\001\033[1;32m\002"
# define R_C "\001\033[1;31m\002"
# define N_C "\001\033[0m\002"
#endif
