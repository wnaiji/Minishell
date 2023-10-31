/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walidnaiji <walidnaiji@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 10:57:16 by wnaiji            #+#    #+#             */
/*   Updated: 2023/10/26 15:50:19 by walidnaiji       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_builtin	token_builtin(char *str)
{
	if (ft_strncmp(str, "echo", 5) == 0)
		return (ECHO);
	else if (ft_strncmp(str, "cd", 3) == 0)
		return (CD);
	else if (ft_strncmp(str, "pwd", 4) == 0)
		return (PWD);
	else if (ft_strncmp(str, "export", 7) == 0)
		return (EXPORT);
	else if (ft_strncmp(str, "unset", 6) == 0)
		return (UNSET);
	else if (ft_strncmp(str, "env", 4) == 0)
		return (ENV);
	else if (ft_strncmp(str, "exit", 5) == 0)
		return (EXIT);
	else
		return (NO_BUILTIN);
}

char	**split_args(char *str)
{
	char	**args;

	if (!str)
		return (NULL);
	args = ft_split(str, ' ');
	return (args);
}

char	*strtolower(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		str[i] = ft_tolower(str[i]);
		i++;
	}
	return (str);
}
