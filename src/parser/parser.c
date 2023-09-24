/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walidnaiji <walidnaiji@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 10:56:57 by wnaiji            #+#    #+#             */
/*   Updated: 2023/09/24 12:35:18 by walidnaiji       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
/*
-Dans les fonctions Infile et Outfile ne pas supprimer les maillons mais à la place
	remplacer l'operator par CMD
-Dans les foinctions Infile et Outfile ne stocker dans le parser seulement la str
-Par la suite les NO_OPERATOR restant seront des commandes ou des builtins
	- si elle est précédé d'un pipe il faudra mettre en IO IN_PIPE
	- si elle est précédé d'un infile il faudra mettre en IO IN_FILE
	- si elle est suivi d'un NO_OPERATOR
-la fonction is_infile et is_outfile me semble correcte, commencer celui des cmd
-Un nouvel enum est mis en place dans la structure de la liste chaîne du parser
	elle determinera le stdin et le stdout lors de l'éxécution de la commande
-une fois que la liste et construite, que la vérification des enum
	est bon, que le split des arguments et bon, il faudra trim
	tout les operateurs
-pour terminé la vérification de la norme et des leaks sur la fin
	de ce parsing*/
t_parser	*is_infile(t_lexer **lexer, t_parser *parser)
{
	char	*tmp;

	tmp = NULL;
	if (!*lexer)
		return (parser);
	while (*lexer)
	{
		if ((*lexer)->operator == INFILE || (*lexer)->operator == HEREDOC)
		{
			parser = parser_add_back_list(parser, NULL);
			parser->str = ft_strdup((*lexer)->str);
			parser->operator = (*lexer)->operator;
			parser->builtin = NO_BUILTIN;
			parser->io = NO_IO;
			*lexer = delete_node(*lexer);
			init_node_infile(&parser, &*lexer, &tmp);
		}
		else if (!(*lexer)->next)
			break ;
		else
			*lexer = (*lexer)->next;
	}
	return (parser);
}

t_parser	*is_outfile(t_lexer **lexer, t_parser *parser)
{
	char	*tmp;

	tmp = NULL;
	if (!*lexer)
		return (parser);
	while (*lexer)
	{
		if ((*lexer)->operator == OUTFILE || (*lexer)->operator == OUTFILE_AP_MOD)
		{
			parser = parser_add_back_list(parser, NULL);
			parser->str = ft_strdup((*lexer)->str);
			parser->operator = (*lexer)->operator;
			parser->builtin = NO_BUILTIN;
			parser->io = NO_IO;
			*lexer = delete_node(*lexer);
			init_node_outfile(&parser, &(*lexer), &tmp);
		}
		else if (!(*lexer)->next)
			break ;
		else
			*lexer = (*lexer)->next;
	}
	return (parser);
}

t_parser	*is_cmd_or_builtin(t_lexer **lexer, t_parser *parser)
{
	char	*tmp;

	tmp = NULL;
	if (!*lexer)
		return (parser);
	while (*lexer)
	{
		parser = parser_add_back_list(parser, NULL);
		if ((*lexer)->operator == NO_OPERATOR)
		{
			if ((*lexer)->prev)
		}
		*lexer = (*lexer)->next;
	}
	return (parser);
}



void	init_parser(t_lexer *lexer)
{
	t_parser	*parser;

	parser = NULL;
	parser = is_infile(&lexer, parser);
	if (lexer)
	{
		while (lexer->prev)
			lexer = lexer->prev;
	}
	parser = is_outfile(&lexer, parser);
	print_parser(parser);
	if (lexer)
	{
		while (lexer->prev)
			lexer = lexer->prev;
	}
	parser = is_cmd_or_builtin(&lexer, parser);
	//if (parser)
	//{				/*j'ai oublié pk j'ai fait cette boucle*/
	//	while (parser->prev)
	//		parser = parser->prev;
	//}
	//parser = init_node_parser(parser);
}
