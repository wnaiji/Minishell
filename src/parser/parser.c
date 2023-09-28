/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walidnaiji <walidnaiji@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 10:56:57 by wnaiji            #+#    #+#             */
/*   Updated: 2023/09/28 21:32:18 by walidnaiji       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
/*
-pour pouvoir différencier un SPACE de " " il faudra split les args cmds
	dés le début et non par la suite car une fois les arguments concaténé
	on ne poura plus faire la différence entre un SPACE et " "
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

unsigned int	nbr_arg_cmd(unsigned int nb_arg, t_lexer *lexer)
{
	while (lexer && lexer->operator == NO_OPERATOR)
	{
		lexer = lexer->next;
		if (lexer && lexer->operator == SPACE
			&& lexer->next->operator == NO_OPERATOR)
		{
			nb_arg++;;
			lexer = lexer->next;
		}
	}
	return (nb_arg);
}

t_parser	*is_cmd_or_builtin(t_lexer **lexer, t_parser *parser)
{
	unsigned int	nb_arg;
	int				index;

	while (*lexer)
	{
		nb_arg = 1;
		if ((*lexer)->operator == NO_OPERATOR)
		{
			parser = parser_add_back_list(parser, NULL);
			index = -1;
			nb_arg = nbr_arg_cmd(nb_arg, *lexer);
			while (*lexer && (*lexer)->operator == NO_OPERATOR)
			{
				init_node_cmd(&parser, &*lexer, nb_arg, ++index);
				if (*lexer && (*lexer)->operator == SPACE
					&& (*lexer)->next->operator == NO_OPERATOR)
				{
					*lexer = (*lexer)->next;
					init_node_cmd(&parser, &*lexer, nb_arg, ++index);
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
	//print_lexer(lexer);
	print_parser(parser);
}
