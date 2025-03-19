/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walidnaiji <walidnaiji@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:39:37 by ncardozo          #+#    #+#             */
/*   Updated: 2023/12/12 23:01:21 by walidnaiji       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	put_error(char *arg)
{
	ft_putstr_fd("minishell: export: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd(": not a valid identifier", 2);
	g_sig = 1;
}

t_var_list	*list_export_add_back_list(t_var_list *list, char *str)
{
	t_var_list	*newnode;
	t_var_list	*tmp;

	tmp = list;
	newnode = malloc(sizeof(t_var_list));
	if (!newnode)
		return (NULL);
	newnode->name = ft_strdup(str);
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

void	*delete_node_export(t_var_list *list)
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
	free(list->name);
	free(list);
	return (pointer);
}
