/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_fonctions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncardozo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 21:14:39 by ncardozo          #+#    #+#             */
/*   Updated: 2023/11/02 20:08:54 by ncardozo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_exit(t_tools *tools, int code)
{
	if (code == EXIT_SUCCESS)
	{
		free(tools->command_line);
		tools->command_line = NULL;
		exit(EXIT_SUCCESS);
	}
	else if (code == MALLOC_ERROR)
	{
		free_struct_string(tools);
		free(tools);
		exit(1);
	}
}
