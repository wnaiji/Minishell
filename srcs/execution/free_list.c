/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walidnaiji <walidnaiji@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 02:18:27 by wnaiji            #+#    #+#             */
/*   Updated: 2023/12/12 18:22:49 by walidnaiji       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_sublist(t_sublist *sublist)
{
	t_sublist	*tmp_sub;
	int			i;

	tmp_sub = sublist;
	while (tmp_sub)
	{
		i = 0;
		while (tmp_sub->str[i])
			free(tmp_sub->str[i++]);
		free(tmp_sub->str);
		tmp_sub = delete_node_sublist(tmp_sub);
	}
}

void	free_list_exec(t_list_exec *list)
{
	t_list_exec	*tmp_list;

	tmp_list = list;
	while (tmp_list)
	{
		free_sublist(tmp_list->sublist);
		tmp_list = delete_node_list(tmp_list);
	}
}

void	*delete_node_list(t_list_exec *list)
{
	void	*pointer;

	pointer = NULL;
	if (list->before && list->next)
	{
		pointer = list->next;
		list->before->next = list->next;
		list->next->before = list->before;
	}
	else if (!list->before && list->next)
	{
		pointer = list->next;
		list->next->before = NULL;
	}
	else if (list->before && !list->next)
	{
		pointer = list->before;
		list->before->next = NULL;
	}
	free(list);
	return (pointer);
}

void	*delete_node_sublist(t_sublist *sublist)
{
	void	*pointer;

	pointer = NULL;
	if (sublist->before && sublist->next)
	{
		pointer = sublist->next;
		sublist->before->next = sublist->next;
		sublist->next->before = sublist->before;
	}
	else if (!sublist->before && sublist->next)
	{
		pointer = sublist->next;
		sublist->next->before = NULL;
	}
	else if (sublist->before && !sublist->next)
	{
		pointer = sublist->before;
		sublist->before->next = NULL;
	}
	free(sublist);
	return (pointer);
}
