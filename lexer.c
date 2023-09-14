/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walidnaiji <walidnaiji@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 16:30:39 by wnaiji            #+#    #+#             */
/*   Updated: 2023/09/14 14:47:06 by walidnaiji       ###   ########.fr       */
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
	if (lexer->str)
		lexer = ft_add_back_list(lexer, NULL);
	if (lexer->next)
		lexer = lexer->next;
	while (input[(*i)++] != SIMPLE_QUOTE)
		len++;
	lexer->str = ft_substr(input, start, len);
	lexer->quoted = SIMPLE_QUOTED;
	lexer->operator = NO_OPERATOR;
	if (input[*i] == DOUBLE_QUOTE)
		lexer = double_quote(lexer, input, &(*i));
	else if (input[*i] == SIMPLE_QUOTE)
		lexer = simple_quote(lexer, input, &(*i));
	return (lexer);
}

t_lexer	*double_quote(t_lexer *lexer, char *input, int *i)
{
	int	len;
	int	start;

	len = 0;
	(*i)++;
	start = *i;
	if (lexer->str)
		lexer = ft_add_back_list(lexer, NULL);
	if (lexer->next)
		lexer = lexer->next;
	while (input[(*i)++] != DOUBLE_QUOTE)
		len++;
	lexer->str = ft_substr(input, start, len);
	lexer->quoted = DOUBLE_QUOTED;
	lexer->operator = NO_OPERATOR;
	if (input[*i] == SIMPLE_QUOTE)
		lexer = simple_quote(lexer, input, &(*i));
	else if (input[*i] == DOUBLE_QUOTE)
		lexer = double_quote(lexer, input, &(*i));
	return (lexer);
}

t_lexer	*no_quote(t_lexer *lexer, char *input, int *i)
{
	char	*tmp;

	tmp = NULL;
	if (lexer->str)
		lexer = ft_add_back_list(lexer, NULL);
	if (lexer->next)
		lexer = lexer->next;
	while (input[*i])
	{
		if (special_char(input[*i]) != 0)
			break ;
		else
		{
			if (!tmp)
				tmp = chardup(input[*i]);
			else
				tmp = charjoin(tmp, input[*i]);
			(*i)++;
		}
	}
	lexer->str = ft_strtrim(tmp, " ");
	free(tmp);
	lexer->quoted = NO_QUOTED;
	lexer->operator = NO_OPERATOR;
	lexer = check_space(lexer, input, &(*i));
	return (lexer);
}

t_lexer	*operator(t_lexer *lexer, char *input, int *i)
{
	if (lexer->str)
		lexer = ft_add_back_list(lexer, NULL);
	if (lexer->next)
		lexer = lexer->next;
	if (special_char(input[*i]) != 0)
		lexer->str = chardup(input[*i]);
	if ((input[*i] == '<' && input[*i + 1] == '<')
		|| (input[*i] == '>' && input[*i + 1] == '>'))
		lexer->str = charjoin(lexer->str, input[*i]);
	lexer->quoted = NO_QUOTED;
	return (lexer);
}

void	init_lexer(char *input)
{
	int		i;
	t_lexer	*lexer;

	i = 0;
	lexer = NULL;
	while (input[i])
	{
		lexer = ft_add_back_list(lexer, NULL);
		lexer = check_space(lexer, input, &i);
		if (lexer->next)
			lexer = lexer->next;
		if (input[i] == SIMPLE_QUOTE)
			lexer = simple_quote(lexer, input, &i);
		else if (input[i] == DOUBLE_QUOTE)
			lexer = double_quote(lexer, input, &i);
		else if (input[i] != DOUBLE_QUOTE || input[i] != SIMPLE_QUOTE)
		{
			lexer = no_quote(lexer, input, &i);
			if (input[i])
			{
				lexer = operator(lexer, input, &i);
				lexer->operator = token_operator(lexer->str, &i);
			}
		}
		i++;
	}
	while (lexer->prev)
		lexer = lexer->prev;
	if (ft_last_content(lexer) == NULL)
		lexer = ft_delete_at_back(lexer);
	print_lexer(lexer);
}
