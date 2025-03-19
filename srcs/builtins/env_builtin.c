/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walidnaiji <walidnaiji@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 10:03:02 by ncardozo          #+#    #+#             */
/*   Updated: 2023/12/12 22:25:57 by walidnaiji       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	env_builtin(t_tools *tools, char **cmd)
{
	int		iter;

	iter = 0;
	if (cmd[1])
	{
		dup2(STDERR_FILENO, STDOUT_FILENO);
		printf("minishell: %s: No such file or directoy\n", cmd[1]);
		g_sig = 127;
		return ;
	}
	if (!tools->env)
		return ;
	while (tools->env[iter])
	{
		if (ft_strchr(tools->env[iter], '=') != 0)
			ft_putendl_fd(tools->env[iter], STDOUT_FILENO);
		++iter;
	}
	g_sig = 0;
}
