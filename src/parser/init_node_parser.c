/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_node_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walidnaiji <walidnaiji@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 14:45:06 by wnaiji            #+#    #+#             */
/*   Updated: 2023/10/31 18:54:50 by walidnaiji       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	nbr_infile(t_lexer *lexer)
{
	int		nbr_file;
	t_lexer	*tmp;

	nbr_file = 0;
	tmp = lexer;
	while (tmp && tmp->operator != PIPE)
	{
		if (tmp->operator == INFILE || tmp->operator == HEREDOC)
			nbr_file++;
		tmp = tmp->next;
	}
	return (nbr_file);
}

int	nbr_outfile(t_lexer *lexer)
{
	int		nbr_file;
	t_lexer	*tmp;

	nbr_file = 0;
	tmp = lexer;
	while (tmp && tmp->operator != PIPE)
	{
		if (tmp->operator == OUTFILE
			|| tmp->operator == OUTFILE_AP_MOD)
			nbr_file++;
		tmp = tmp->next;
	}
	return (nbr_file);
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

void	init_node_cmd(t_parser **parser, t_lexer **lexer,
			unsigned int nb_arg, int i)
{
	char		*tmp;

	if ((*parser)->cmd)
	{
		(*parser)->cmd = malloc(sizeof(char *) * (nb_arg + 1));
		if (!(*parser)->cmd)
			return ;
	}
	(*parser)->cmd[i] = ft_strdup((*lexer)->str);
	(*parser)->cmd[i + 1] = NULL;
	*lexer = delete_node(*lexer);
	while (*lexer && (*lexer)->operator == NO_OPERATOR)
	{
		tmp = ft_strjoin((*parser)->cmd[i], (*lexer)->str);
		free((*parser)->cmd[i]);
		(*parser)->cmd[i] = ft_strdup(tmp);
		free(tmp);
		*lexer = delete_node(*lexer);
	}
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
