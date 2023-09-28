/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_node_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walidnaiji <walidnaiji@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 14:45:06 by wnaiji            #+#    #+#             */
/*   Updated: 2023/09/28 21:35:36 by walidnaiji       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	init_node_infile(t_parser **parser, t_lexer **lexer)
{
	*parser = parser_add_back_list(*parser, NULL);
	(*parser)->str = ft_strdup((*lexer)->str);
	(*parser)->cmd = NULL;
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
	(*parser)->cmd = NULL;
	(*parser)->operator = (*lexer)->operator;
	(*parser)->builtin = NO_BUILTIN;
	(*parser)->output = OUT_FILE;
	(*parser)->input = NO_INPUT;
	*lexer = (*lexer)->next;
	if (*lexer && ((*lexer)->operator == SPACE))
		*lexer = (*lexer)->next;
}

void	init_node_cmd(t_parser **parser, t_lexer **lexer,
		unsigned int nb_arg, int	i)
{
	char		*tmp;

	if (!(*parser)->cmd)
	{
		(*parser)->cmd = malloc(sizeof(char *) * (nb_arg + 5));
		if (!(*parser)->cmd)
			return ;
	}
	(*parser)->cmd[i] = ft_strdup((*lexer)->str);
	while ((*lexer)->next && (*lexer)->next->operator == NO_OPERATOR)
	{
		tmp = ft_strjoin((*parser)->cmd[i], (*lexer)->str);
		free((*parser)->cmd[i]);
		(*parser)->cmd[i] = ft_strdup(tmp);
		free(tmp);
		*lexer = (*lexer)->next;
	}
	(*parser)->cmd[i + 1] = NULL;
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
