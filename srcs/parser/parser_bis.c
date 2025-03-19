/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bis.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncardozo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 20:20:09 by ncardozo          #+#    #+#             */
/*   Updated: 2023/12/11 20:21:06 by ncardozo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_sublist	*init_node_infile(t_node **lexer, t_sublist *sublist)
{
	int	token;

	if (*lexer && ((*lexer)->type == TOKEN_INPUT_REDIRECT
			|| (*lexer)->type == TOKEN_REDIRECT_HEREDOC))
	{
		if ((*lexer)->type == TOKEN_INPUT_REDIRECT)
			token = INFILE;
		else
			token = HERE_DOC;
		sublist = sublist_add_back_list(sublist, is_infile(&(*lexer)));
		while (sublist->next)
			sublist = sublist->next;
		sublist->tok = token;
	}
	return (sublist);
}

t_sublist	*init_node_outfile(t_node **lexer, t_sublist *sublist)
{
	int	token;

	if (*lexer && ((*lexer)->type == TOKEN_OUTPUT_REDIRECT
			|| (*lexer)->type == TOKEN_REDIRECT_APPEND))
	{
		if ((*lexer)->type == TOKEN_OUTPUT_REDIRECT)
			token = OUTFILE;
		else
			token = AP_MOD;
		sublist = sublist_add_back_list(sublist, is_outfile(&(*lexer)));
		while (sublist->next)
			sublist = sublist->next;
		sublist->tok = token;
	}
	return (sublist);
}

t_sublist	*init_node_cmd(t_node **lexer, t_sublist *sublist)
{
	if (*lexer && (*lexer)->before)
		while ((*lexer)->before)
			*lexer = (*lexer)->before;
	if (*lexer && ((*lexer)->type == TOKEN_SPACE || (*lexer)->type == TOKEN_WORD
			|| (*lexer)->type == TOKEN_BT_SIMPLE_QUOTES
			|| (*lexer)->type == TOKEN_BT_DOUBLE_QUOTES))
	{
		while (*lexer && (*lexer)->type == TOKEN_SPACE)
			*lexer = delete_node_lexer(*lexer);
		sublist = sublist_add_back_list(sublist, is_cmd(&(*lexer)));
		while (sublist->next)
			sublist = sublist->next;
		sublist->tok = CMD;
	}
	return (sublist);
}
