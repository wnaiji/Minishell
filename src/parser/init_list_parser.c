/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_list_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walidnaiji <walidnaiji@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 13:44:02 by wnaiji            #+#    #+#             */
/*   Updated: 2023/09/16 15:19:18 by walidnaiji       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	*parser_add_back_list(t_parser *list, char *line)
{
	t_parser	*newline;
	t_parser	*tmp;

	tmp = list;
	newline = malloc(sizeof(t_parser));
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

void	*delete_node(t_parser *list)
{
	void	*nxt;

	if (!list)
		return (list);
	if (list->next == NULL)
	{
		free(list);
		return (list);
	}
	else if (list->prev == NULL)
	{
		nxt = list->next;
		free(list);
		return (nxt);
	}
	nxt = list->next;
	list->prev->next = list->next;
	free(list);
	return (nxt);
}

void	*parser_delete_at_back(t_parser *list)
{
	t_parser	*tmp;
	t_parser	*tmp2;

	tmp = list;
	tmp2 = list;
	if (!list)
		return (list);
	if (list->next == NULL)
	{
		free(list);
		return (list);
	}
	while (tmp->next)
	{
		tmp2 = tmp;
		tmp = tmp->next;
	}
	tmp2->next = NULL;
	free(tmp);
	return (list);
}

char	*parser_last_content(t_parser *list)
{
	t_parser	*tmp;

	tmp = list;
	if (!list)
		return (0);
	while (tmp->next)
		tmp = tmp->next;
	return (tmp->str);
}
