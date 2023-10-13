/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walidnaiji <walidnaiji@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 10:56:57 by wnaiji            #+#    #+#             */
/*   Updated: 2023/10/13 16:22:03 by walidnaiji       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_parser	*is_infile(t_lexer **lexer, t_parser *parser)
{
	char	*tmp;

	tmp = NULL;
	while (*lexer)
	{
		if ((*lexer)->operator == INFILE || (*lexer)->operator == HEREDOC)
		{
			init_node_infile(&parser, &*lexer);
			while (*lexer && (*lexer)->operator == NO_OPERATOR)
			{
				tmp = ft_strjoin(parser->str, (*lexer)->str);
				free(parser->str);
				parser->str = ft_strdup(tmp);
				free(tmp);
				(*lexer)->operator = CMD;
				*lexer = (*lexer)->next;
			}
		}
		else
			*lexer = (*lexer)->next;
	}
	return (parser);
}

t_parser	*is_outfile(t_lexer **lexer, t_parser *parser)
{
	char	*tmp;

	tmp = NULL;
	while (*lexer)
	{
		if ((*lexer)->operator == OUTFILE
			|| (*lexer)->operator == OUTFILE_AP_MOD)
		{
			init_node_outfile(&parser, &*lexer);
			while (*lexer && (*lexer)->operator == NO_OPERATOR)
			{
				tmp = ft_strjoin(parser->str, (*lexer)->str);
				free(parser->str);
				parser->str = ft_strdup(tmp);
				free(tmp);
				(*lexer)->operator = CMD;
				*lexer = (*lexer)->next;
			}
		}
		else
			*lexer = (*lexer)->next;
	}
	return (parser);
}

t_parser	*is_cmd(t_lexer **lexer, t_parser *parser,
				unsigned int nb_arg, int index)
{
	while (*lexer)
	{
		nb_arg = 1;
		if ((*lexer)->operator == NO_OPERATOR)
		{
			parser = parser_add_back_list(parser, NULL);
			index = 0;
			nb_arg = nbr_arg_cmd(nb_arg, *lexer);
			while (*lexer && (*lexer)->operator == NO_OPERATOR)
			{
				init_node_cmd(&parser, &*lexer, nb_arg, index++);
				if (*lexer && (*lexer)->operator == SPACE
					&& (*lexer)->next->operator == NO_OPERATOR)
				{
					*lexer = (*lexer)->next;
					init_node_cmd(&parser, &*lexer, nb_arg, index++);
					if (*lexer && (*lexer)->operator == SPACE)
						*lexer = (*lexer)->next;
				}
			}
		}
		else
			*lexer = (*lexer)->next;
	}
	return (parser);
}

t_parser	*is_builtin(t_parser *parser)
{
	t_parser	*first_node;

	while (parser->prev)
		parser = parser->prev;
	first_node = parser;
	while (parser)
	{
		if (parser->operator == CMD)
			parser = init_node_builtin(parser);
		parser = parser->next;
	}
	parser = first_node;
	return (parser);
}

void	init_parser(t_lexer *lexer)
{
	t_parser		*parser;
	t_lexer			*first_node;
	unsigned int	nb_arg;
	int				index;

	parser = NULL;
	first_node = lexer;
	nb_arg = 1;
	index = 0;
	parser = is_infile(&lexer, parser);
	lexer = first_node;
	parser = is_outfile(&lexer, parser);
	lexer = first_node;
	parser = is_cmd(&lexer, parser, nb_arg, index);
	parser = is_builtin(parser);
	print_parser(parser);
}
