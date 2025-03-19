/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncardozo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 08:20:19 by ncardozo          #+#    #+#             */
/*   Updated: 2023/12/02 11:53:58 by ncardozo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	reset_tools(t_tools *tools)
{
	free(tools->command_line);
	minishell_loop(tools->env);
	return (1);
}

void	reset_ex_tools(t_tools *ex_tools)
{
	free(ex_tools->command_line);
	if (ex_tools->result)
		free(ex_tools->result);
	if (ex_tools->out)
		free(ex_tools->out);
	if (ex_tools->data)
		free(ex_tools->data);
}
