/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walidnaiji <walidnaiji@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 16:30:39 by wnaiji            #+#    #+#             */
/*   Updated: 2023/09/22 23:27:36 by walidnaiji       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_lexer	*operator(t_lexer *lexer, char *input, int *i)
{
	lexer->str = chardup(input[*i]);
	if ((input[*i] == '<' && input[*i + 1] == '<')
		|| (input[*i] == '>' && input[*i + 1] == '>'))
		lexer->str = charjoin(lexer->str, input[*i]);
	lexer->quoted = NO_QUOTED;
	lexer->operator = token_operator(input);
	if (lexer->operator == HEREDOC || lexer->operator == OUTFILE_AP_MOD)
		(*i)++;
	return (lexer);
}

t_lexer	*is_cmd(t_lexer *lexer, char *input, int *i)
{
	if (special_char(input[*i]) == 0 && input[*i] != DOUBLE_QUOTE
		&& input[*i] != SIMPLE_QUOTE)
		lexer->str = chardup(input[(*i)++]);
	while(input[*i] && special_char(input[*i]) == 0
		&& input[*i] != DOUBLE_QUOTE && input[*i] != SIMPLE_QUOTE
		&& input[*i] != ' ')
	{
		lexer->str = charjoin(lexer->str, input[*i]);
		(*i)++;
	}
	lexer->quoted = NO_QUOTED;
	lexer->operator = NO_OPERATOR;
	(*i)--;
	return (lexer);
}

t_lexer	*space(t_lexer *lexer, char *input, int *i)
{
	lexer = lexer_add_back_list(lexer, NULL);
	if (lexer->next)
		lexer = lexer->next;
	lexer->str = chardup(input[*i]);
	if (input[*i + 1] == ' ')
	{
		*i = forward_in_space(input, &(*i));
		(*i)--;
	}
	lexer->quoted = NO_QUOTED;
	lexer->operator = SPACE;
	return (lexer);
}

t_lexer	*final_check_lexer(t_lexer *lexer)
{
	t_lexer	*tmp;

	tmp = lexer;
	while (tmp)
	{
		if (tmp->str[0] == '\0')
			tmp = delete_node(tmp);
		tmp = tmp->next;
	}
	return (lexer);
}

t_lexer	*init_lexer(char *input)
{
	int		i;
	char	*str;
	t_lexer	*lexer;

	i = 0;
	str = ft_strtrim(input, " ");
	free(input);
	lexer = NULL;
	while (str[i])
	{
		if (str[i] == SIMPLE_QUOTE)
			lexer = simple_quote(lexer, str, &i);
		else if (str[i] == DOUBLE_QUOTE)
			lexer = double_quote(lexer, str, &i);
		else if (str[i] == ' ')
			lexer = space(lexer, str, &i);
		else
			lexer = no_quote(lexer, str, &i);
		i++;
	}
	while (lexer && lexer->prev)
		lexer = lexer->prev;
	if (lexer)
		lexer = final_check_lexer(lexer);
	print_lexer(lexer);
	return (lexer);
}
