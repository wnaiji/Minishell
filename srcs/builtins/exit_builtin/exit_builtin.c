/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walidnaiji <walidnaiji@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 22:25:47 by ncardozo          #+#    #+#             */
/*   Updated: 2023/12/12 18:35:27 by walidnaiji       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	exit_nbr_of_arg_error_output(void)
{
	ft_putstr_fd("minishell: exit: too many arguments\n", 2);
	exit(FAILURE);
}

void	exit_with_code(char **str)
{
	int		exit_code;
	long	val;

	exit_code = 0;
	if (str[1])
	{
		if (is_str_digit(str[1]))
		{
			val = ft_strto_l(str[1], NULL);
			exit_code = (int)(val % 256);
			if (exit_code < 0)
				exit_code += 256;
		}
		else
		{
			dup2(STDERR_FILENO, STDOUT_FILENO);
			printf("minishell: %s: numeric argument required\n", str[1]);
			exit_code = 255;
		}
	}
	free_array(str);
	exit(exit_code);
}

void	exit_builtin(char **arg)
{
	if (!arg[1])
	{
		ft_putendl_fd("exit", STDERR_FILENO);
		arg = NULL;
		exit(SUCCESS);
	}
	else if (arg[1] && !arg[2])
		exit_with_code(arg);
	else
		exit_nbr_of_arg_error_output();
}
