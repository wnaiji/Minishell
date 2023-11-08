/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_list_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walidnaiji <walidnaiji@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 13:44:02 by wnaiji            #+#    #+#             */
/*   Updated: 2023/11/08 15:00:49 by walidnaiji       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	*parser_add_back_list(t_parser *parser, char **str)
{
	t_parser	*newnode;
	t_parser	*tmp;

	tmp = parser;
	newnode = malloc(sizeof(t_parser));
	if (!newnode)
		return (NULL);
	newnode->infile = str;
	newnode->outfile = NULL;
	newnode->cmd = NULL;
	newnode->prev = NULL;
	newnode->next = NULL;
	if (!parser)
		return (newnode);
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = newnode;
		newnode->prev = tmp;
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

