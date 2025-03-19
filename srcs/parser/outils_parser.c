/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walidnaiji <walidnaiji@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 10:57:16 by wnaiji            #+#    #+#             */
/*   Updated: 2023/12/03 14:36:22 by walidnaiji       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	nbr_pipe(t_node *lexer)
{
	int		nbr;
	t_node	*tmp;

	nbr = 0;
	tmp = lexer;
	while (tmp)
	{
		if (tmp->type == TOKEN_PIPE)
			nbr++;
		tmp = tmp->next;
	}
	return (nbr);
}

int	nbr_arg_cmd(t_node *lexer)
{
	int		nbr_arg;
	t_node	*tmp;

	tmp = lexer;
	nbr_arg = 0;
	while (tmp && tmp->type != TOKEN_PIPE)
	{
		if (tmp && (tmp->type == TOKEN_WORD
				|| tmp->type == TOKEN_BT_DOUBLE_QUOTES
				|| tmp->type == TOKEN_BT_SIMPLE_QUOTES))
			nbr_arg++;
		tmp = tmp->next;
	}
	return (nbr_arg);
}

int	last_content_lexer(t_node *lexer)
{
	t_node	*listtmp;

	listtmp = lexer;
	if (!lexer)
		return (0);
	while (listtmp->next)
		listtmp = listtmp->next;
	return (listtmp->type);
}
