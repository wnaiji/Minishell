/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walidnaiji <walidnaiji@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 10:56:57 by wnaiji            #+#    #+#             */
/*   Updated: 2023/09/22 10:57:05 by walidnaiji       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
/*
-Au niveau de la fonction infile quand nous notons une redirestion
	outfile le premier maillon est dupliqué
-La fonction is_infile est correcte en terme de gestion et de retour
	de liste chaîné, corriger les 2 autres avant de continuer
-Verifier les fonctions lists au niveau des suppresions de maillon
	si les valeur donné à prev et next sont bien correct pour le bon
	fonctionement de la lecture des listes
-la découpe des commandes ou des redirections ne sont pas correcte
	quand aucune espace n'est mise, elle devra donc couper a la
	rencontre d'un opperateur
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
		return (NULL);
	while (*lexer)
	{
		if ((*lexer)->operator == INFILE || (*lexer)->operator == HEREDOC)
		{
			parser = parser_add_back_list(parser, NULL);
			if (parser->next)
				parser = parser->next;
			parser->str = ft_strdup((*lexer)->str);
			parser->redirection = (*lexer)->operator;
			parser->builtin = NO_BUILTIN;
			*lexer = delete_node(*lexer);
			while (*lexer && ((*lexer)->operator == NO_OPERATOR
				|| (*lexer)->operator == SPACE))
			{
				tmp = ft_strjoin(parser->str, (*lexer)->str);
				free(parser->str);
				parser->str = ft_strdup(tmp);
				free(tmp);
				*lexer = delete_node(*lexer);
			}
		}
		else if (*lexer)
			*lexer = (*lexer)->next;
	}
	return (parser);
}

t_parser	*is_outfile(t_lexer **lexer, t_parser *parser)
{
	char	*tmp;

	tmp = NULL;
	if (!*lexer)
		return (NULL);
	while ((*lexer)->next)
	{
		if ((*lexer)->operator == OUTFILE || (*lexer)->operator == OUTFILE_AP_MOD)
		{
			parser = parser_add_back_list(parser, NULL);
			if (parser->next)
				parser = parser->next;
			parser->str = ft_strdup((*lexer)->str);
			parser->redirection = (*lexer)->operator;
			parser->builtin = NO_BUILTIN;
			*lexer = delete_node(*lexer);
			while (*lexer && ((*lexer)->operator == NO_OPERATOR
				|| (*lexer)->operator == SPACE))
			{
				tmp = ft_strjoin(parser->str, (*lexer)->str);
				free(parser->str);
				parser->str = ft_strdup(tmp);
				free(tmp);
				*lexer = delete_node(*lexer);
			}
		}
		else if (*lexer)
			*lexer = (*lexer)->next;
	}
	return (parser);
}

t_parser	*is_cmd_or_builtin(t_lexer **lexer, t_parser *parser)
{
	char	*tmp;

	tmp = NULL;
	if (!*lexer)
		return (NULL);
	while ((*lexer)->next)
	{
		parser = parser_add_back_list(parser, NULL);
		if (parser->next)
			parser = parser->next;
		while ((*lexer)->next && (*lexer)->operator != PIPE)
		{
			if (!parser->str)
				parser->str = ft_strdup((*lexer)->str);
			else
			{
				tmp = ft_strdup(parser->str);
				free(parser->str);
				parser->str = ft_strjoin(tmp, (*lexer)->str);
			}
			*lexer = delete_node(*lexer);
		}
		parser->redirection = CMD;
		if ((*lexer)->next)
			*lexer = delete_node(*lexer);
	}
	if (parser_last_content(parser) == NULL)
		parser = parser_delete_at_back(parser);
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
	//parser = is_outfile(&lexer, parser);
	if (lexer)
	{
		while (lexer->prev)
			lexer = lexer->prev;
	}
	//parser = is_cmd_or_builtin(&lexer, parser);
	if (parser)
	{
		while (parser->prev)
			parser = parser->prev;
	}
	//parser = init_node_parser(parser);
	print_parser(parser);
}
