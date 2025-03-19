/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walidnaiji <walidnaiji@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 09:02:14 by ncardozo          #+#    #+#             */
/*   Updated: 2023/12/12 22:26:56 by walidnaiji       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_n_option(const char *arg)
{
	int	iter;

	if (arg[0] != '-')
		return (0);
	iter = 1;
	while (arg[iter] != '\0')
	{
		if (arg[iter] != 'n')
			return (0);
		++iter;
	}
	return (1);
}

void	echo_builtin(char **arg)
{
	int	iter;
	int	n_flag;

	iter = 1;
	n_flag = 0;
	while (arg[iter] && is_n_option(arg[iter]))
	{
		n_flag = 1;
		iter++;
	}
	while (arg[iter])
	{
		printf("%s", arg[iter]);
		if (arg[iter + 1])
			printf(" ");
		++iter;
	}
	if (!n_flag)
		printf("\n");
	g_sig = 0;
}
