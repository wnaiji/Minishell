/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walidnaiji <walidnaiji@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 10:56:57 by wnaiji            #+#    #+#             */
/*   Updated: 2023/12/11 22:45:56 by walidnaiji       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_sublist	*init_sublist(t_node **lexer)
{
	t_sublist	*sublist;

	sublist = NULL;
	while (*lexer && (*lexer)->next && (*lexer)->type != TOKEN_PIPE)
	{
		sublist = init_node_infile(&(*lexer), sublist);
		sublist = init_node_outfile(&(*lexer), sublist);
		if (*lexer && (*lexer)->next && (*lexer)->type == TOKEN_SPACE
			&& (*lexer)->next->type != TOKEN_WORD
			&& (*lexer)->next->type != TOKEN_BT_SIMPLE_QUOTES
			&& (*lexer)->next->type != TOKEN_BT_DOUBLE_QUOTES)
			*lexer = delete_node_lexer(*lexer);
		if (*lexer && (*lexer)->type != TOKEN_INPUT_REDIRECT
			&& (*lexer)->type != TOKEN_REDIRECT_HEREDOC
			&& (*lexer)->type != TOKEN_OUTPUT_REDIRECT
			&& (*lexer)->type != TOKEN_REDIRECT_APPEND
			&& (*lexer)->type != TOKEN_PIPE)
			if ((*lexer)->next)
				*lexer = (*lexer)->next;
	}
	if (*lexer)
		while ((*lexer)->before)
			*lexer = (*lexer)->before;
	sublist = init_node_cmd(&(*lexer), sublist);
	return (sublist);
}

static void	token_pipe_error_message(void)
{
	ft_putendl_fd("minishell: syntax error near \
unexpected token `|'", STDERR_FILENO);
	g_sig = 258;
}

t_list_exec	*init_parser(t_node *lexer)
{
	t_list_exec	*list;

	list = NULL;
	if (!lexer)
		return (list);
	if (last_content_lexer(lexer) == TOKEN_PIPE)
	{
		token_pipe_error_message();
		return (list);
	}
	lexer = lexer_add_back_list(lexer, "|");
	while (lexer)
	{
		list = list_exec_add_back_list(list, init_sublist(&lexer));
		if (lexer)
		{
			while (lexer->before)
				lexer = lexer->before;
			if (lexer->type == TOKEN_PIPE)
				lexer = delete_node_lexer(lexer);
		}
	}
	list = init_node_builtin(list);
	list = last_content_list(list);
	return (list);
}
