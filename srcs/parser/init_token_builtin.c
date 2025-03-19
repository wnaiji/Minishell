/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_token_builtin.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walidnaiji <walidnaiji@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 14:45:06 by wnaiji            #+#    #+#             */
/*   Updated: 2023/11/30 03:29:18 by walidnaiji       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_builtin	token_builtin(char *str)
{
	if (ft_strncmp(str, "echo", 5) == 0)
		return (ECHO);
	else if (ft_strncmp(str, "cd", 3) == 0)
		return (CD);
	else if (ft_strncmp(str, "pwd", 4) == 0)
		return (PWD);
	else if (ft_strncmp(str, "export", 7) == 0)
		return (EXPORT);
	else if (ft_strncmp(str, "unset", 6) == 0)
		return (UNSET);
	else if (ft_strncmp(str, "env", 4) == 0)
		return (ENV);
	else if (ft_strncmp(str, "exit", 5) == 0)
		return (EXIT);
	else
		return (NO_BUILTIN);
}

char	*strtolower(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		str[i] = ft_tolower(str[i]);
		i++;
	}
	return (str);
}

t_list_exec	*init_node_builtin(t_list_exec *parser)
{
	char		*tmp_cmd;
	t_list_exec	*tmp_parser;
	t_sublist	*tmp_sublist;

	tmp_parser = parser;
	tmp_sublist = NULL;
	while (tmp_parser)
	{
		tmp_sublist = tmp_parser->sublist;
		while (tmp_sublist && tmp_sublist->tok != CMD)
			tmp_sublist = tmp_sublist->next;
		if (tmp_sublist)
		{
			tmp_cmd = ft_strdup(tmp_sublist->str[0]);
			tmp_cmd = strtolower(tmp_cmd);
			tmp_sublist->builtin = token_builtin(tmp_cmd);
			free(tmp_cmd);
		}
		tmp_parser = tmp_parser->next;
	}
	return (parser);
}
