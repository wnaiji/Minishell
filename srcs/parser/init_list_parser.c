/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_list_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walidnaiji <walidnaiji@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 13:44:02 by wnaiji            #+#    #+#             */
/*   Updated: 2023/12/04 00:20:45 by walidnaiji       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_list_exec	*list_exec_add_back_list(t_list_exec *list, t_sublist *sublist)
{
	t_list_exec	*newnode;
	t_list_exec	*tmp;

	tmp = list;
	newnode = malloc(sizeof(t_list_exec));
	if (!newnode)
		return (NULL);
	newnode->sublist = sublist;
	newnode->before = NULL;
	newnode->next = NULL;
	if (!list)
		return (newnode);
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = newnode;
		newnode->before = tmp;
		return (list);
	}
}

t_sublist	*sublist_add_back_list(t_sublist *sublist, char **str)
{
	t_sublist	*newnode;
	t_sublist	*tmp;

	tmp = sublist;
	newnode = malloc(sizeof(t_sublist));
	if (!newnode)
		return (NULL);
	newnode->str = str;
	newnode->before = NULL;
	newnode->next = NULL;
	if (!sublist)
		return (newnode);
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = newnode;
		newnode->before = tmp;
		return (sublist);
	}
}

t_node	*lexer_add_back_list(t_node *lexer, char *str)
{
	t_node	*newnode;
	t_node	*tmp;

	tmp = lexer;
	newnode = malloc(sizeof(t_node));
	if (!newnode)
		return (NULL);
	newnode->data = ft_strdup(str);
	newnode->type = TOKEN_PIPE;
	newnode->before = NULL;
	newnode->next = NULL;
	if (!lexer)
		return (newnode);
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = newnode;
		newnode->before = tmp;
		return (lexer);
	}
}

void	*delete_node_lexer(t_node *lexer)
{
	void	*pointer;

	pointer = NULL;
	if (lexer->before && lexer->next)
	{
		pointer = lexer->next;
		lexer->before->next = lexer->next;
		lexer->next->before = lexer->before;
	}
	else if (!lexer->before && lexer->next)
	{
		pointer = lexer->next;
		lexer->next->before = NULL;
	}
	else if (lexer->before && !lexer->next)
	{
		pointer = lexer->before;
		lexer->before->next = NULL;
	}
	free(lexer->data);
	free(lexer);
	return (pointer);
}

t_list_exec	*last_content_list(t_list_exec *parser)
{
	t_list_exec	*listtmp;

	listtmp = parser;
	if (!parser)
		return (0);
	while (listtmp->next)
		listtmp = listtmp->next;
	if (!listtmp->sublist)
	{
		listtmp->before->next = NULL;
		free(listtmp);
	}
	return (parser);
}
