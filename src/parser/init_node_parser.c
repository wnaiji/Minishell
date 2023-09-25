/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_node_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walidnaiji <walidnaiji@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 14:45:06 by wnaiji            #+#    #+#             */
/*   Updated: 2023/09/25 16:58:28 by walidnaiji       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	init_node_infile(t_parser **parser, t_lexer **lexer)
{
	*parser = parser_add_back_list(*parser, NULL);
	(*parser)->str = ft_strdup((*lexer)->str);
	(*parser)->operator = (*lexer)->operator;
	(*parser)->builtin = NO_BUILTIN;
	(*parser)->input = IN_FILE;
	(*parser)->output = NO_OUTPUT;
	*lexer = (*lexer)->next;
	if (*lexer && ((*lexer)->operator == SPACE))
		*lexer = (*lexer)->next;
}

void	init_node_outfile(t_parser **parser, t_lexer **lexer)
{
	*parser = parser_add_back_list(*parser, NULL);
	(*parser)->str = ft_strdup((*lexer)->str);
	(*parser)->operator = (*lexer)->operator;
	(*parser)->builtin = NO_BUILTIN;
	(*parser)->output = OUT_FILE;
	(*parser)->input = NO_INPUT;
	*lexer = (*lexer)->next;
	if (*lexer && ((*lexer)->operator == SPACE))
		*lexer = (*lexer)->next;
}

void	init_node_cmd(t_parser **parser, t_lexer **lexer)
{
	char	*tmp;

	tmp = NULL;
	if (!(*parser)->str)
		(*parser)->str = ft_strdup((*lexer)->str); // mettre les éléments directement dans **cmd
	else
	{
		tmp = ft_strjoin((*parser)->str, (*lexer)->str);
		free((*parser)->str);
		(*parser)->str = ft_strdup(tmp);
		free(tmp);
	}
	(*parser)->operator = CMD;
	(*parser)->builtin = NO_BUILTIN;
	(*parser)->input = input(*lexer);
	(*parser)->output = output(*lexer);
	*lexer = (*lexer)->next;
}

t_parser	*init_node_parser(t_parser *parser)
{
	if (!parser)
		return (NULL);
	while (parser->next)
	{
		parser->cmd = split_args(parser->str);
		parser->cmd[0] = strtolower(parser->cmd[0], parser->operator);
		// ne pas tolower quand c'est un infile ou outfile
		parser->builtin = is_builtin(parser->cmd[0]);
		free(parser->str);
		parser = parser->next;
	}
	return (parser);
}
