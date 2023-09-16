/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walidnaiji <walidnaiji@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 10:56:57 by wnaiji            #+#    #+#             */
/*   Updated: 2023/09/16 15:13:25 by walidnaiji       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_parser	*is_infile(t_lexer *lexer, t_parser *parser)
{
	char	*tmp;

	tmp = NULL;
	if (!lexer)
		return (NULL);
	parser = parser_add_back_list(parser, NULL);
	if (parser->next)
		parser = parser->next;
	while (lexer->next)
	{
		if (lexer->operator == INFILE || lexer->operator == HEREDOC)
		{
			parser->str = ft_strdup(lexer->str);
			parser->redirection = lexer->operator;
			parser->builtin = NO_BUILTIN;
			lexer = delete_node(lexer);
			while (lexer->next && lexer->operator != SPACE)
			{
				tmp = ft_strjoin(parser->str, lexer->str);
				free(parser->str);
				parser->str = ft_strdup(tmp);
				free(tmp);
				lexer = delete_node(lexer);
			}
			parser = parser_add_back_list(parser, NULL);
			if (parser->next)
				parser = parser->next;
		}
		lexer = lexer->next;
	}
	if (parser_last_content(parser) == NULL)
		parser = parser_delete_at_back(parser);
	return (parser);
}

//is_builtin
//Utiliser cette fonction apres avoir split les arguments
//il faudre tolower la premiere string et seulement apres
//lui donné le bon enum

t_parser	*is_cmd_or_builtin(t_lexer *lexer, t_parser *parser)
{
	char	*tmp;

	tmp = NULL;
	if (!lexer)
		return (NULL);
	while (lexer->next)
	{
		parser = parser_add_back_list(parser, NULL);
		if (parser->next)
			parser = parser->next;
		while (lexer->next && lexer->operator != PIPE)
		{
			if (!parser->str)
				parser->str = ft_strdup(lexer->str);
			else
			{
				tmp = ft_strdup(parser->str);
				free(parser->str);
				parser->str = ft_strjoin(tmp, lexer->str);
			}
			lexer = delete_node(lexer);
		}
		parser->redirection = CMD;
		if (lexer->next)
			lexer = delete_node(lexer);
	}
	if (parser_last_content(parser) == NULL)
		parser = parser_delete_at_back(parser);
	return (parser);
}

t_parser	*is_outfile(t_lexer *lexer, t_parser *parser)
{
	char	*tmp;

	tmp = NULL;
	if (!lexer)
		return (NULL);
	parser = parser_add_back_list(parser, NULL);
	if (parser->next)
		parser = parser->next;
	while (lexer->next)
	{
		if (lexer->operator == OUTFILE || lexer->operator == OUTFILE_AP_MOD)
		{
			parser->str = ft_strdup(lexer->str);
			parser->redirection = lexer->operator;
			parser->builtin = NO_BUILTIN;
			lexer = delete_node(lexer);
			while (lexer->next && lexer->operator != SPACE)
			{
				tmp = ft_strjoin(parser->str, lexer->str);
				free(parser->str);
				parser->str = ft_strdup(tmp);
				free(tmp);
				lexer = delete_node(lexer);
			}
			parser = parser_add_back_list(parser, NULL);
			if (parser->next)
				parser = parser->next;
		}
		lexer = lexer->next;
	}
	if (parser_last_content(parser) == NULL)
		parser = parser_delete_at_back(parser);
	return (parser);
}

void	init_parser(t_lexer *lexer)
{
	t_parser	*parser;

	parser = NULL;
	parser = is_infile(lexer, parser);
	if (lexer)
	{
		while (lexer->prev)
			lexer = lexer->prev;
	}
	parser = is_outfile(lexer, parser);
	if (lexer)
	{
		while (lexer->prev)
			lexer = lexer->prev;
	}
	parser = is_cmd_or_builtin(lexer, parser);
	if (parser)
	{
		while (parser->prev)
			parser = parser->prev;
	}
	parser = init_node_parser(parser);
}
