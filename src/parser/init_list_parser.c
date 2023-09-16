/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_list_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walidnaiji <walidnaiji@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 13:44:02 by wnaiji            #+#    #+#             */
/*   Updated: 2023/09/16 17:53:44 by walidnaiji       ###   ########.fr       */
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

void	*delete_node(t_lexer *list)
{
	t_lexer	*tmp;
	void	*pointer;

	tmp = list->next;
	//if (!list)
	//	return (list);
	if (list->prev && list->next)
	{
		list->prev->next = list->next;
		list->next->prev = list->prev;
		free(list);// il faudra eventuellement faire
		//en sorte de passer au maillon suivant avant
		//de return
		return (tmp);
	}
	else if (!list->prev && list->next)
	{
		pointer = list->next;
		list->next->prev = NULL;
		free(list);
		return (pointer);
	}
	else if (list->prev && !list->next)
	{
		pointer = list->prev;
		list->prev->next = NULL;
		free(list);
		return (pointer);
	}
	free(list);
	return (NULL);
}

void	*parser_delete_at_back(t_parser *list)
{
	t_parser	*tmp;

	tmp = list;
	if (!list)
		return (list);
	if (!tmp->next && !tmp->prev)
	{
		free(list);
		return (NULL);
	}
	while (tmp)
		tmp = tmp->next;
	if (tmp->prev)
		tmp->prev->next = NULL;
	if (!list->next)
		list = list->prev;
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
