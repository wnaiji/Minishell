/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_special_cases.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walidnaiji <walidnaiji@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 19:44:01 by ncardozo          #+#    #+#             */
/*   Updated: 2023/12/11 16:15:28 by walidnaiji       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	prompt_back_cases(t_tools *tools)
{
	if (((ft_strncmp(tools->command_line, ":", 1) == 0) && \
			(ft_strlen(tools->command_line) == 1)) || \
			((ft_strncmp(tools->command_line, "!", 1) == 0) && \
			(ft_strlen(tools->command_line) == 1)))
	{
		free(tools->command_line);
		tools->command_line = NULL;
		g_sig = 1;
		minishell_loop(tools->env);
	}
}
