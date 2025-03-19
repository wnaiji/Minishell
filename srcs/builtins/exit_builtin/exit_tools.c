/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walidnaiji <walidnaiji@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 08:49:19 by ncardozo          #+#    #+#             */
/*   Updated: 2023/12/11 16:15:28 by walidnaiji       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	skip_spaces(const char **str)
{
	while (**str == ' ')
		++(*str);
}

static int	handle_sign(const char **str)
{
	int	sign;

	sign = 1;
	if (**str == '+' || **str == '-')
	{
		if (**str == '-')
			sign = -1;
		++(*str);
	}
	return (sign);
}

static int	char_to_digit(const char **str)
{
	int	digit;

	digit = **str - '0';
	++(*str);
	return (digit);
}

static long	handle_overflow(long result, int digit, int sign)
{
	long	overflow_result;

	if (result > (LONG_MAX - digit) / 10)
	{
		g_sig = ERANGE;
		if (sign == 1)
		{
			overflow_result = LONG_MAX;
		}
		else
		{
			overflow_result = LONG_MIN;
		}
		return (overflow_result);
	}
	return (result * 10 + digit);
}

long	ft_strto_l(const char *str, char **endptr)
{
	long	result;
	int		sign;
	int		digit;

	result = 0;
	skip_spaces(&str);
	sign = handle_sign(&str);
	while (*str >= '0' && *str <= '9')
	{
		digit = char_to_digit(&str);
		result = handle_overflow(result, digit, sign);
	}
	if (endptr != NULL)
		*endptr = (char *)str;
	return (result * sign);
}
