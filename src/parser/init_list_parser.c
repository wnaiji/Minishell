/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_list_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walidnaiji <walidnaiji@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 13:44:02 by wnaiji            #+#    #+#             */
/*   Updated: 2023/09/22 23:24:37 by walidnaiji       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	*parser_add_back_list(t_parser *parser, char *str)
{
	t_parser	*newline;
	t_parser	*tmp;

	tmp = parser;
	newline = malloc(sizeof(t_parser));
	if (!newline)
		return (NULL);
	newline->str = str;
	newline->prev = NULL;
	newline->next = NULL;
	if (!parser)
		return (newline);
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = newline;
		newline->prev = tmp;
		return (parser);
	}
}



void	*parser_delete_at_back(t_parser *parser)
{
	t_parser	*tmp;

	tmp = parser;
	if (!parser)
		return (parser);
	if (!tmp->next && !tmp->prev)
	{
		free(parser);
		return (NULL);
	}
	while (tmp)
		tmp = tmp->next;
	if (tmp->prev)
		tmp->prev->next = NULL;
	if (!parser->next)
		parser = parser->prev;
	free(tmp);
	return (parser);
}

char	*parser_last_content(t_parser *parser)
{
	t_parser	*tmp;

	tmp = parser;
	if (!parser)
		return (0);
	while (tmp->next)
		tmp = tmp->next;
	return (tmp->str);
}
