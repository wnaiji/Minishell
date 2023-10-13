/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_node_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walidnaiji <walidnaiji@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 14:45:06 by wnaiji            #+#    #+#             */
/*   Updated: 2023/10/13 16:08:06 by walidnaiji       ###   ########.fr       */
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
			unsigned int nb_arg, int i)
{
	char		*tmp;

	if (!(*parser)->cmd)
	{
		(*parser)->cmd = malloc(sizeof(char *) * (nb_arg + 1));
		if (!(*parser)->cmd)
			return ;
	}
	(*parser)->cmd[i + 1] = NULL;
	(*parser)->operator = CMD;
	(*parser)->builtin = NO_BUILTIN;
	(*parser)->input = input(*lexer);
	(*parser)->output = output(*lexer);
	(*parser)->cmd[i] = ft_strdup((*lexer)->str);
	*lexer = (*lexer)->next;
	while (*lexer && (*lexer)->operator == NO_OPERATOR)
	{
		tmp = ft_strjoin((*parser)->cmd[i], (*lexer)->str);
		free((*parser)->cmd[i]);
		(*parser)->cmd[i] = ft_strdup(tmp);
		free(tmp);
		*lexer = (*lexer)->next;
	}
}

unsigned int	nbr_arg_cmd(unsigned int nb_arg, t_lexer *lexer)
{
	while (lexer && lexer->operator == NO_OPERATOR)
	{
		lexer = lexer->next;
		if (lexer && lexer->operator == SPACE
			&& lexer->next->operator == NO_OPERATOR)
		{
			nb_arg++;
			lexer = lexer->next;
		}
	}
	return (nb_arg);
}

t_parser	*init_node_builtin(t_parser *parser)
{
	char	*tmp_cmd;

	tmp_cmd = ft_strdup(parser->cmd[0]);
	tmp_cmd = strtolower(tmp_cmd);
	parser->builtin = token_builtin(tmp_cmd);
	free(tmp_cmd);
	return (parser);
}
