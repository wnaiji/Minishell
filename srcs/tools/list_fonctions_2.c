/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_fonctions_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncardozo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 15:24:16 by ncardozo          #+#    #+#             */
/*   Updated: 2023/12/05 23:04:26 by ncardozo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	*delete_node(t_node *list)
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
	else
		return (NULL);
	free(list->data);
	free(list);
	return (pointer);
}

void	free_list_vars(t_node *list)
{
	if (list->var_name)
		free(list->var_name);
	if (list->var_value)
		free(list->var_value);
}

void	pop_front_node(t_node **list)
{
	t_node	*temp;

	if ((*list) == NULL)
		return ;
	temp = (*list);
	if (temp->next != NULL)
	{
		free_list_vars(temp);
		temp->next->before = NULL;
		(*list) = temp->next;
	}
	else
		(*list) = NULL;
	free(temp);
}

void	pop_back_list(t_node **list)
{
	t_node	*temp;
	t_node	*before;

	if (list == NULL)
		return ;
	temp = (*list);
	before = NULL;
	while (temp->next != NULL)
	{
		before = temp;
		temp = temp->next;
	}
	if (before != NULL)
		before->next = NULL;
	else
		(*list) = NULL;
	free_node_data(temp);
	free(temp);
}
