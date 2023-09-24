/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_node_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walidnaiji <walidnaiji@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 14:45:06 by wnaiji            #+#    #+#             */
/*   Updated: 2023/09/24 10:42:05 by walidnaiji       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	init_node_infile(t_parser **parser, t_lexer **lexer, char **tmp)
{
	if (*lexer && ((*lexer)->operator == SPACE))
		*lexer = delete_node(*lexer);
	while (*lexer && ((*lexer)->operator == NO_OPERATOR
		|| (*lexer)->operator == SPACE || (*lexer)->operator == INFILE
		|| (*lexer)->operator == HEREDOC))
	{
		*tmp = ft_strjoin((*parser)->str, (*lexer)->str);
		free((*parser)->str);
		(*parser)->str = ft_strdup(*tmp);
		free(*tmp);
		*lexer = delete_node(*lexer);
		if (*lexer && ((*lexer)->operator == SPACE))
		{
			*lexer = delete_node(*lexer);
			break ;
		}
		else if (*lexer && ((*lexer)->operator == INFILE
			|| (*lexer)->operator == HEREDOC))
			break ;
	}
}

void	init_node_outfile(t_parser **parser, t_lexer **lexer, char **tmp)
{
	if (*lexer && ((*lexer)->operator == SPACE))
		*lexer = delete_node(*lexer);
	while (*lexer && ((*lexer)->operator == NO_OPERATOR
		|| (*lexer)->operator == SPACE || (*lexer)->operator == OUTFILE
		|| (*lexer)->operator == OUTFILE_AP_MOD))
	{
		*tmp = ft_strjoin((*parser)->str, (*lexer)->str);
		free((*parser)->str);
		(*parser)->str = ft_strdup(*tmp);
		free(*tmp);
		*lexer = delete_node(*lexer);
		if (*lexer && ((*lexer)->operator == SPACE))
		{
			*lexer = delete_node(*lexer);
			break ;
		}
		else if (*lexer && ((*lexer)->operator == OUTFILE
			|| (*lexer)->operator == OUTFILE_AP_MOD))
			break ;
	}
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
