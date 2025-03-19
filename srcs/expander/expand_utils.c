/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncardozo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 16:10:59 by ncardozo          #+#    #+#             */
/*   Updated: 2023/11/28 23:25:37 by ncardozo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_redirect_or_append(t_node *actual)
{
	if (actual->type == TOKEN_INPUT_REDIRECT || \
		actual->type == TOKEN_OUTPUT_REDIRECT || \
		actual->type == TOKEN_REDIRECT_APPEND)
		return (TRUE);
	return (FALSE);
}

int	is_heredoc_redirec(t_node *actual)
{
	if (actual->type == TOKEN_REDIRECT_HEREDOC)
		return (TRUE);
	return (FALSE);
}

t_node	*pop_first_unexistant_var(t_node **actual, t_node **list)
{
	pop_front_node(list);
	return ((*actual) = (*list));
}

t_node	*pop_unexistant_var(t_node **actual)
{
	t_node	*new_head;

	new_head = delete_node(*actual);
	return ((*actual) = new_head);
}

void	remove_node_if_needed(t_node **list, t_node *node)
{
	if (!node->before && !node->next)
		pop_front_node(list);
	else if (!node->before && node->next)
		pop_first_unexistant_var(&node, list);
	else
		pop_unexistant_var(&node);
}
