/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_node_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walidnaiji <walidnaiji@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 14:45:06 by wnaiji            #+#    #+#             */
/*   Updated: 2023/09/23 16:47:42 by walidnaiji       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	init_node_infile(t_parser **parser, t_lexer **lexer, char **tmp)
{
	*parser = parser_add_back_list(*parser, NULL);
	if ((*parser)->next)
		*parser = (*parser)->next;
	(*parser)->str = ft_strdup((*lexer)->str);
	(*parser)->operator = (*lexer)->operator;
	(*parser)->builtin = NO_BUILTIN;
	(*parser)->io = NO_IO;
	*lexer = delete_node(*lexer);
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
	}
}

void	init_node_outfile(t_parser **parser, t_lexer **lexer, char **tmp)
{
	*parser = parser_add_back_list(*parser, NULL);
	if ((*parser)->next)
		*parser = (*parser)->next;
	(*parser)->str = ft_strdup((*lexer)->str);
	(*parser)->operator = (*lexer)->operator;
	(*parser)->builtin = NO_BUILTIN;
	(*parser)->io = NO_IO;
	*lexer = delete_node(*lexer);
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
	}
}
