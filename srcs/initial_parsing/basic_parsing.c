/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walidnaiji <walidnaiji@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 14:54:56 by wnaiji            #+#    #+#             */
/*   Updated: 2023/12/07 17:47:19 by walidnaiji       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_simple_quote(char *str, int *i)
{
	while (str[*i])
	{
		if (str[*i] == SIMPLE_QUOTE)
			return (0);
		else if (str[*i + 1] == '\0')
			return (1);
		*i = *i + 1;
	}
	return (1);
}

int	check_double_quote(char *str, int *i)
{
	while (str[*i])
	{
		if (str[*i] == DOUBLE_QUOTE)
			return (0);
		else if (str[*i + 1] == '\0')
			return (1);
		*i = *i + 1;
	}
	return (1);
}

int	basic_parsing(char *input)
{
	int		i;

	i = 0;
	while (input[i])
	{
		if (input[i] == SIMPLE_QUOTE)
		{
			i++;
			if (check_simple_quote(input, &i) == 1)
				return (1);
		}
		else if (input[i] == DOUBLE_QUOTE)
		{
			i++;
			if (check_double_quote(input, &i) == 1)
				return (1);
		}
		else if (input[i] == BACKSLASH || input[i] == POINT_VIRGULE)
			return (1);
		i++;
	}
	return (0);
}
