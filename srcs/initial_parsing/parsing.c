/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncardozo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 07:38:12 by ncardozo          #+#    #+#             */
/*   Updated: 2023/12/11 20:17:53 by ncardozo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_wrong_number_of_argc(int ac)
{
	if (ac > 1)
	{
		printf(B_C "Please launch minishell with no arguments");
		printf(V_C " \"./minishell + ENTER\"\n" N_C);
		exit(1);
	}
}

int	is_empty_line(char *str)
{
	int	iter;
	int	count;
	int	line_len;

	iter = -1;
	count = 0;
	line_len = ft_strlen(str);
	if (str == NULL)
		return (TRUE);
	while (str[++iter])
	{
		if (str[iter] < 33)
			++count;
	}
	if (count == line_len)
		return (TRUE);
	return (FALSE);
}

int	check_if_quoted_string(t_tools *tools)
{
	if (basic_parsing(tools->command_line) == ODD_QUOTES)
		return (ODD_QUOTES);
	return (ZERO_QUOTES);
}
