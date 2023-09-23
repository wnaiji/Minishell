/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walidnaiji <walidnaiji@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 10:56:57 by wnaiji            #+#    #+#             */
/*   Updated: 2023/09/23 17:08:26 by walidnaiji       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
/*
-il faudra pouvoir séparer en deux maillons quand nous avons a faire à plusieurs
	infile collé sans espaces ex: <in<in
-Un nouvel enum est mis en place dans la structure de la liste chaîne du parser
	elle determinera le stdin et le stdout lors de l'éxécution de la commande
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
		return (parser);
	while (*lexer)
	{
		if ((*lexer)->operator == INFILE || (*lexer)->operator == HEREDOC)
		{
			init_node_infile(&parser, &(*lexer), &tmp);
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
		return (parser);
	while (*lexer)
	{
		if ((*lexer)->operator == OUTFILE || (*lexer)->operator == OUTFILE_AP_MOD)
		{
			init_node_outfile(&parser, &(*lexer), &tmp);
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
		parser->operator = CMD;
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
	parser = is_outfile(&lexer, parser);
	print_parser(parser);
	if (lexer)
	{
		while (lexer->prev)
			lexer = lexer->prev;
	}
	//parser = is_cmd_or_builtin(&lexer, parser);
	//if (parser)
	//{				/*j'ai oublié pk j'ai fait cette boucle*/
	//	while (parser->prev)
	//		parser = parser->prev;
	//}
	//parser = init_node_parser(parser);
}
