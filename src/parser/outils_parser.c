/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walidnaiji <walidnaiji@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 10:57:16 by wnaiji            #+#    #+#             */
/*   Updated: 2023/09/24 15:02:48 by walidnaiji       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "parser.h"

int	is_builtin(char *str)
{
	if (ft_strncmp(str, "echo", 4) == 0)
		return (ECHO);
	else if (ft_strncmp(str, "cd", 2) == 0)
		return (CD);
	else if (ft_strncmp(str, "pwd", 3) == 0)
		return (PWD);
	else if (ft_strncmp(str, "export", 6) == 0)
		return (EXPORT);
	else if (ft_strncmp(str, "unset", 5) == 0)
		return (UNSET);
	else if (ft_strncmp(str, "env", 3) == 0)
		return (ENV);
	else if (ft_strncmp(str, "exit", 4) == 0)
		return (EXIT);
	else
		return (NO_BUILTIN);
}

char	**split_args(char *str)
{
	char	**args;

	if (!str)
		return NULL;
	args = ft_split(str, ' ');
	return (args);
}

char	*strtolower(char *str, int operator)
{
	int	i;

	i = 0;
	while (str[i] && operator == CMD)
	{
		str[i] = ft_tolower(str[i]);
		i++;
	}
	return (str);
}

t_input	input()
{

}

t_output	output()
{
	
}
