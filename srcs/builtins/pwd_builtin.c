/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walidnaiji <walidnaiji@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 09:44:39 by ncardozo          #+#    #+#             */
/*   Updated: 2023/12/12 22:25:39 by walidnaiji       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	pwd_builtin(char **arg)
{
	char	cwd[PATH_MAX];

	if (arg[1] && arg[1][0] == '-')
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(arg[1], STDERR_FILENO);
		ft_putendl_fd(": invalid option", STDERR_FILENO);
		g_sig = 1;
		return ;
	}
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		ft_putendl_fd(cwd, STDOUT_FILENO);
	else
		perror("pwd error");
	g_sig = 0;
}
