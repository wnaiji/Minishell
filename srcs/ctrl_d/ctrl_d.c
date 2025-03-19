/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncardozo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 23:04:24 by ncardozo          #+#    #+#             */
/*   Updated: 2023/12/11 18:31:13 by ncardozo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_ctrl_d_inter_mode(t_tools *tools, char *temp)
{
	if (temp == NULL)
	{
		ft_putendl_fd("exit", STDERR_FILENO);
		free_env(tools->env);
		exit(SUCCESS);
	}
}
