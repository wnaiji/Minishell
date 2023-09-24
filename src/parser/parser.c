/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walidnaiji <walidnaiji@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 10:56:57 by wnaiji            #+#    #+#             */
/*   Updated: 2023/09/24 15:10:58 by walidnaiji       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
/*
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
	while (*lexer)
	{
		if ((*lexer)->operator == OUTFILE || (*lexer)->operator == OUTFILE_AP_MOD)
		{
			init_node_outfile(&parser, &(*lexer));
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
	while (*lexer)
	{
		if ((*lexer)->operator == NO_OPERATOR)
		{
			parser = parser_add_back_list(parser, NULL);
			parser->str = ft_strdup((*lexer)->str); // mettre les éléments directement dans **cmd
			parser->operator = CMD;
			parser->builtin = NO_BUILTIN;
			parser->input = input();
			parser->output = output();
			if ((*lexer)->prev)
		}
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
	print_lexer(lexer);
	print_parser(parser);
}
