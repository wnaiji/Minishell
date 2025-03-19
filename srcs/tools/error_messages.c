/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_messages.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walidnaiji <walidnaiji@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:16:11 by ncardozo          #+#    #+#             */
/*   Updated: 2023/12/11 21:21:13 by walidnaiji       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*handle_memory_allocation_error(void)
{
	ft_putendl_fd(MSG_ERROR_MEMORY, STDOUT_FILENO);
	return (NULL);
}

void	norm_write_error(ssize_t ret)
{
	if (ret == -1)
	{
		perror("write() error");
		return ;
	}
}

void	error_messages(t_tools *tools)
{
	ft_putstr_fd("minishell :", 2);
	ft_putstr_fd("syntax error near unexpected token \'", 2);
	ft_putstr_fd(&tools->quote_type, 2);
	ft_putendl_fd("\'", 2);
	g_sig = 258;
	free(tools->command_line);
	tools->command_line = NULL;
	minishell_loop(tools->env);
}
