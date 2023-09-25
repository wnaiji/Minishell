/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walidnaiji <walidnaiji@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 10:56:57 by wnaiji            #+#    #+#             */
/*   Updated: 2023/09/25 17:45:22 by walidnaiji       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
/*
-faire en sorte que "cat -e" soit dans le même maillon
-split les cmds puis vérifier le premier str du tableau via strlower
	si c'est un builtin
-une fois que la liste et construite, que la vérification des enum
	est bon, que le split des arguments et bon, il faudra trim
	tout les operateurs
-pour terminé la vérification de la norme et des leaks sur la fin
	de ce parsing*/
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
		if ((*lexer)->operator == OUTFILE || (*lexer)->operator == OUTFILE_AP_MOD)
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

t_parser	*is_cmd_or_builtin(t_lexer **lexer, t_parser *parser)
{
	while (*lexer)
	{
		if ((*lexer)->operator == NO_OPERATOR)
		{
			parser = parser_add_back_list(parser, NULL);
			init_node_cmd(&parser, &*lexer);
			if (*lexer)
			{
				while (*lexer && (*lexer)->operator == NO_OPERATOR)
				{
					init_node_cmd(&parser, &*lexer);
					if (*lexer && (*lexer)->operator == SPACE
						&& (*lexer)->next->operator == NO_OPERATOR)
						init_node_cmd(&parser, &*lexer);
					else if (*lexer)
						*lexer = (*lexer)->next;
				}
			}

		}
		else
			*lexer = (*lexer)->next;
	}
	return (parser);
}



void	init_parser(t_lexer *lexer)
{
	t_parser	*parser;
	t_lexer		*first_node;

	parser = NULL;
	first_node = lexer;
	parser = is_infile(&lexer, parser);
	lexer = first_node;
	parser = is_outfile(&lexer, parser);
	lexer = first_node;
	parser = is_cmd_or_builtin(&lexer, parser);
	lexer = first_node;
	//parser = init_node_parser(parser);
	print_parser(parser);
}
