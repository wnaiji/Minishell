/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils_lexer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walidnaiji <walidnaiji@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 11:07:25 by wnaiji            #+#    #+#             */
/*   Updated: 2023/09/14 14:44:23 by walidnaiji       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_lexer	*check_space(t_lexer *lexer, char *input, int *i)
{
	while (input[*i] && (input[*i] == ' ' || input[*i] == '\t'))
		(*i)++;
	if (input[*i] == DOUBLE_QUOTE)
		lexer = double_quote(lexer, input, &(*i));
	else if (input[*i] == SIMPLE_QUOTE)
		lexer = simple_quote(lexer, input, &(*i));
	return (lexer);
}

t_operator	token_operator(char *str, int *i)
{
	if (!str)
		return (99);
	if (str[0] == '|')
		return (PIPE);
	else if (str[0] == '<' && str[1] == '<')
	{
		(*i)++;
		return (HEREDOC);
	}
	else if (str[0] == '<')
		return (INFILE);
	else if (str[0] == '>' && str[1] == '>')
	{
		(*i)++;
		return (OUTFILE_AP_MOD);
	}
	else if (str[0] == ' ')
		return (SPACE);
	else
		return (OUTFILE);
}

char	*chardup(char c)
{
	char	*str;

	str = malloc(sizeof(char) * 2);
	if (!str)
		return (NULL);
	str[0] = c;
	str[1] = '\0';
	return (str);
}

char	*charjoin(char *str, char c)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = malloc(sizeof(char) * ft_strlen(str) + 2);
	if (!tmp)
		return (NULL);
	while (str[i])
	{
		tmp[i] = str[i];
		i++;
	}
	tmp[i] = c;
	tmp[i + 1] = '\0';
	free(str);
	return (tmp);
}

int	special_char(char c)
{
	if (c == '>' || c == '<' || c == PIPELINE || c == SIMPLE_QUOTE
		|| c == DOUBLE_QUOTE)
		return (c);
	else
		return (0);
}
