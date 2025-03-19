/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_fonctions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncardozo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 23:12:38 by ncardozo          #+#    #+#             */
/*   Updated: 2023/12/11 20:18:38 by ncardozo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	tokenize_string_between_quotes(t_tools *tools, t_node **list)
{
	int		internal_iter;
	char	*dst;

	search_type_of_quote(tools);
	tools->string_len = 0;
	tools->iter += 1;
	internal_iter = tools->iter;
	while (tools->command_line[internal_iter] != tools->actual_sep \
			&& (internal_iter < ft_strlen(tools->command_line)))
	{
		++tools->string_len;
		++internal_iter;
	}
	dst = ft_substr(tools->command_line, tools->iter, tools->string_len);
	tools->iter += tools->string_len + 1;
	push_back_list(&(*list), dst, tools->quote_type);
	free(dst);
}

static void	tokenize_regular_string(t_tools *tools, t_node **list)
{
	int		internal_iter;
	char	*dst;

	tools->string_len = 0;
	internal_iter = tools->iter;
	while (is_a_separator(tools->command_line[internal_iter]) == 0 \
			&& (internal_iter < ft_strlen(tools->command_line)))
	{
		++tools->string_len;
		++internal_iter;
	}
	dst = ft_substr(tools->command_line, tools->iter, tools->string_len);
	tools->iter += tools->string_len;
	push_back_list(&(*list), dst, TOKEN_WORD);
	free(dst);
}

void	tokenizer(t_tools *tools, t_node **list)
{
	while (tools->iter < ft_strlen(tools->command_line))
	{
		if (is_a_separator(tools->command_line[tools->iter]) != 0)
		{
			tools->actual_sep = is_a_separator(tools->command_line \
				[tools->iter]);
			if (tools->actual_sep == SIMPLE_QUOTE || \
			tools->actual_sep == DOUBLE_QUOTE)
				tokenize_string_between_quotes(tools, &(*list));
			else if (tools->actual_sep == SPACE)
				tokenize_space_char(tools, &(*list));
			else if (tools->actual_sep == PIPE)
				tokenize_pipe_char(tools, list);
			else if (tools->actual_sep == OUTPUT_REDIRECT \
					|| tools->actual_sep == INPUT_REDIRECT)
				tokenize_redirect_chars(tools, &(*list));
		}
		else if (is_a_separator(tools->command_line[tools->iter]) == 0)
			tokenize_regular_string(tools, &(*list));
	}
}
