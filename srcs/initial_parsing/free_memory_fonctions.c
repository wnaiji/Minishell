/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory_fonctions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walidnaiji <walidnaiji@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 21:59:09 by ncardozo          #+#    #+#             */
/*   Updated: 2023/12/07 14:53:57 by walidnaiji       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_string_variable(char *str)
{
	free(str);
	str = NULL;
}

void	free_node_data(t_node *node)
{
	if (node->data)
		free_string_variable(node->data);
}

static void	del_one_list(t_node *list)
{
	if (!list)
		return ;
	free(list);
}

void	free_list(t_node **list)
{
	t_node	*next;

	if (!list || !*list)
		return ;
	next = (*list)->next;
	if ((*list)->var_name != NULL)
		free((*list)->var_name);
	if ((*list)->var_value != NULL)
		free((*list)->var_value);
	del_one_list(*list);
	free_list(&next);
	(*list) = NULL;
}
