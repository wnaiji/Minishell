/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_list_lexer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walidnaiji <walidnaiji@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 11:20:30 by wnaiji            #+#    #+#             */
/*   Updated: 2023/10/31 19:33:30 by walidnaiji       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	*lexer_add_back_list(t_lexer *list, char *line)
{
	t_lexer	*newline;
	t_lexer	*tmp;

	tmp = list;
	newline = malloc(sizeof(t_lexer));
	if (!newline)
		return (NULL);
	newline->str = line;
	newline->prev = NULL;
	newline->next = NULL;
	if (!list)
		return (newline);
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = newline;
		newline->prev = tmp;
		return (list);
	}
}
