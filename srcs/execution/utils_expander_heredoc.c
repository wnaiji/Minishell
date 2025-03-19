/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expander_heredoc.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walidnaiji <walidnaiji@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 19:20:04 by wnaiji            #+#    #+#             */
/*   Updated: 2023/12/10 15:01:24 by walidnaiji       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	len_expand(char *str, int index)
{
	int	len;

	len = 0;
	if (str[index] == '?')
		return (1);
	while (str[index + len] && ft_isalnum(str[index + len]) == 1)
		len ++;
	return (len);
}

char	*chardup(char c)
{
	char	*str;

	str = malloc(sizeof(char) * 2);
	if (!str)
		return (NULL);
	str[0] = c;
	str[1] = '\0';
	return (str);
}

char	*charjoin(char *str, char c)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = malloc(sizeof(char) * ft_strlen(str) + 2);
	if (!tmp)
		return (NULL);
	while (str[i])
	{
		tmp[i] = str[i];
		i++;
	}
	tmp[i] = c;
	tmp[i + 1] = '\0';
	return (tmp);
}
