/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_management_quoted.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walidnaiji <walidnaiji@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:35:50 by wnaiji            #+#    #+#             */
/*   Updated: 2023/09/14 21:33:09 by walidnaiji       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_lexer	*simple_quote(t_lexer *lexer, char *input, int *i)
{
	int	len;
	int	start;

	len = 0;
	(*i)++;
	start = *i;
	lexer = ft_add_back_list(lexer, NULL);
	if (lexer->next)
		lexer = lexer->next;
	while (input[(*i)++] != SIMPLE_QUOTE)
		len++;
	lexer->str = ft_substr(input, start, len);
	lexer->quoted = SIMPLE_QUOTED;
	lexer->operator = NO_OPERATOR;
	(*i)--;
	return (lexer);
}

t_lexer	*double_quote(t_lexer *lexer, char *input, int *i)
{
	int	len;
	int	start;

	len = 0;
	(*i)++;
	start = *i;
	lexer = ft_add_back_list(lexer, NULL);
	if (lexer->next)
		lexer = lexer->next;
	while (input[(*i)++] != DOUBLE_QUOTE)
		len++;
	lexer->str = ft_substr(input, start, len);
	lexer->quoted = DOUBLE_QUOTED;
	lexer->operator = NO_OPERATOR;
	(*i)--;
	return (lexer);
}

t_lexer	*no_quote(t_lexer *lexer, char *input, int *i)
{
	char	*tmp;

	tmp = NULL;
	lexer = ft_add_back_list(lexer, NULL);
	if (lexer->next)
		lexer = lexer->next;
	if (special_char(input[*i]) != 0)
		lexer = operator(lexer, input, &(*i));
	else
		lexer = is_cmd(lexer, input, &(*i));
	tmp = ft_strtrim(lexer->str, " ");
	free(lexer->str);
	lexer->str = ft_strdup(tmp);
	free(tmp);
	return (lexer);
}
