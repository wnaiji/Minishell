/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_fonctions_2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncardozo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 12:27:05 by ncardozo          #+#    #+#             */
/*   Updated: 2023/12/11 21:05:35 by ncardozo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	tokenize_space_char(t_tools *tools, t_node **list)
{
	if (is_space(tools->command_line[tools->iter + 1]) != 0)
		++tools->iter;
	else
	{
		push_back_list(&(*list), " ", TOKEN_SPACE);
		++tools->iter;
	}
}

void	tokenize_redirect_chars(t_tools *tools, t_node **list)
{
	if (tools->command_line[tools->iter + 1] == tools->actual_sep)
	{
		if (tools->actual_sep == '<')
			push_back_list(&(*list), HEREDOC, TOKEN_REDIRECT_HEREDOC);
		else if (tools->actual_sep == '>')
			push_back_list(&(*list), APPEND_REDIRECT, \
			TOKEN_REDIRECT_APPEND);
		tools->iter += 2;
	}
	else
	{
		if (tools->actual_sep == '<')
			push_back_list(&(*list), "<", TOKEN_INPUT_REDIRECT);
		else if (tools->actual_sep == '>')
			push_back_list(&(*list), ">", TOKEN_OUTPUT_REDIRECT);
		++tools->iter;
	}
}

void	tokenize_pipe_char(t_tools *tools, t_node **list)
{
	push_back_list(&(*list), "|", TOKEN_PIPE);
	++tools->iter;
}
