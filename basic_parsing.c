/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walidnaiji <walidnaiji@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 14:54:56 by wnaiji            #+#    #+#             */
/*   Updated: 2023/09/13 10:44:36 by walidnaiji       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	check_simple_quote(char *str, int *i)
{
	while (1)
	{
		*i = *i + 1;
		if (str[*i] == SIMPLE_QUOTE)
			return (0);
		else if (str[*i + 1] == '\0')
		{
			error_syntax("'");
			return (1);
		}
	}
}

static int	check_double_quote(char *str, int *i)
{
	while (1)
	{
		*i = *i + 1;
		if (str[*i] == DOUBLE_QUOTE)
			return (0);
		else if (str[*i + 1] == '\0')
		{
			error_syntax("\"");
			return (1);
		}
	}
}

void	basic_parsing(char *input)
{
	int		i;

	i = 0;
	while (input[i])
	{
		if (input[i] == SIMPLE_QUOTE)
		{
			if (check_simple_quote(input, &i) == 1)
				return ;
		}
		if (input[i] == DOUBLE_QUOTE)
		{
			if (check_double_quote(input, &i) == 1)
				return ;
		}
		if (input[i] == BACKSLASH || input[i] == POINT_VIRGULE)
		{
			error_syntax("\\;");
			return ;
		}
		i++;
	}
	return ;
}
