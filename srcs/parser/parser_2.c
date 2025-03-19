/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walidnaiji <walidnaiji@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 19:16:17 by wnaiji            #+#    #+#             */
/*   Updated: 2023/12/11 22:23:56 by walidnaiji       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*init_str(t_node **lexer)
{
	char	*str;
	char	*tmp;

	str = NULL;
	tmp = NULL;
	while (*lexer && ((*lexer)->type == TOKEN_WORD
			|| (*lexer)->type == TOKEN_BT_SIMPLE_QUOTES
			|| (*lexer)->type == TOKEN_BT_DOUBLE_QUOTES))
	{
		if (!str)
			str = ft_strdup((*lexer)->data);
		else
		{
			tmp = ft_strjoin(str, (*lexer)->data);
			free(str);
			str = ft_strdup(tmp);
			free(tmp);
			tmp = NULL;
		}
		*lexer = delete_node_lexer(*lexer);
	}
	return (str);
}

char	**is_infile(t_node **lexer)
{
	char	**infile;

	infile = malloc(sizeof(char *) * 2);
	if (!infile)
		return (NULL);
	infile[0] = NULL;
	infile[1] = NULL;
	*lexer = delete_node_lexer(*lexer);
	if (*lexer && (*lexer)->type == TOKEN_SPACE)
		*lexer = delete_node_lexer(*lexer);
	infile[0] = init_str(&(*lexer));
	infile[1] = NULL;
	return (infile);
}

char	**is_outfile(t_node **lexer)
{
	char	**outfile;

	outfile = malloc(sizeof(char *) * 2);
	if (!outfile)
		return (NULL);
	outfile[0] = NULL;
	outfile[1] = NULL;
	*lexer = delete_node_lexer(*lexer);
	if (*lexer && (*lexer)->type == TOKEN_SPACE)
		*lexer = delete_node_lexer(*lexer);
	outfile[0] = init_str(&(*lexer));
	outfile[1] = NULL;
	return (outfile);
}

char	**is_cmd(t_node **lexer)
{
	char	**cmd;
	int		i;
	int		nbr_arg;

	i = 0;
	nbr_arg = nbr_arg_cmd(*lexer) + 1;
	cmd = malloc(sizeof(char *) * nbr_arg);
	if (!cmd)
		return (NULL);
	while (i < nbr_arg)
		cmd[i++] = NULL;
	i = 0;
	while (*lexer && (*lexer)->type != TOKEN_PIPE)
	{
		cmd[i] = init_str(&(*lexer));
		if (*lexer && (*lexer)->type == TOKEN_SPACE)
		{
			*lexer = delete_node_lexer(*lexer);
			i++;
		}
		else
			i++;
	}
	cmd[nbr_arg - 1] = NULL;
	return (cmd);
}
