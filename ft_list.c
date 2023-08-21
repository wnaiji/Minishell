/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walidnaiji <walidnaiji@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 11:20:30 by wnaiji            #+#    #+#             */
/*   Updated: 2023/06/07 20:50:37 by walidnaiji       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	*ft_add_front_list(t_list *list, char *line)
{
	t_list	*newline;

	newline = malloc(sizeof(t_list));
	if (!newline)
		return (NULL);
	newline->line = line;
	newline->prev = NULL;
	newline->next = list;
	return (newline);
}

void	*ft_add_back_list(t_list *list, char *line)
{
	t_list	*newline;
	t_list	*tmp;

	tmp = list;
	newline = malloc(sizeof(t_list));
	if (!newline)
		return (NULL);
	newline->line = line;
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

void	*ft_delete_in_head(t_list *list)
{
	t_list	*nxt;

	if (!list)
		return (NULL);
	nxt = list->next;
	free(list);
	return (nxt);
}

void	*ft_delete_at_back(t_list *list)
{
	t_list	*tmp;
	t_list	*tmp2;

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

char	*ft_last_content(t_list *list)
{
	t_list	*tmp;

	tmp = list;
	if (!list)
		return (NULL);
	while (tmp->next)
		tmp = tmp->next;
	return (tmp->line);
}
