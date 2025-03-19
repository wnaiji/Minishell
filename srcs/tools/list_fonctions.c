/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_fonctions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walidnaiji <walidnaiji@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 22:15:37 by ncardozo          #+#    #+#             */
/*   Updated: 2023/12/07 19:18:30 by walidnaiji       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_node	*create_list(void)
{
	t_node	*root;

	root = malloc(sizeof(t_node));
	if (!root)
		return (NULL);
	root = NULL;
	return (root);
}

t_node	*create_new_node(char *data, t_token_type type)
{
	t_node	*new_node;

	new_node = malloc(sizeof(t_node));
	if (new_node != NULL)
	{
		new_node->data = ft_strdup(data);
		new_node->before = NULL;
		new_node->next = NULL;
		new_node->type = type;
	}
	return (new_node);
}

int	list_size(t_node *list)
{
	int	len;

	len = 0;
	while (list)
	{
		list = list->next;
		++len;
	}
	return (len);
}

void	push_back_list(t_node **list, char *data, t_token_type type)
{
	t_node	*new_node;
	t_node	*actual;

	new_node = create_new_node(data, type);
	if ((*list) == NULL)
		(*list) = new_node;
	else
	{
		actual = (*list);
		while (actual->next != NULL)
			actual = actual->next;
		actual->next = new_node;
		new_node->before = actual;
	}
}

void	put_list(t_node *list)
{
	t_node	*actual;

	actual = list;
	while (actual != NULL)
	{
		printf("word : [%s] token : %d  \n\n", actual->data, actual->type);
		actual = actual->next;
	}
}
