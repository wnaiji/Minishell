/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils_expander.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walidnaiji <walidnaiji@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 14:30:17 by wnaiji            #+#    #+#             */
/*   Updated: 2023/11/09 17:07:54 by walidnaiji       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

int	start_expand(char *str, int index)
{
	while (str[index])
	{
		if (str[index] == EXPAND)
			break;
		index++
	}
	return (index + 1);
}

int	len_expand(char *str, int start)
{
	int	len;

	len = 0;
	while (str[index + len] && str[index + len] != ISSPACE)
		len ++;
	return (len);
}
/*cette fonction aura pour but de modifier l'inérieur d'une string*/
char	addstr(char *s1, char *s2, int start, int len)
{

}
