/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walidnaiji <walidnaiji@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 10:57:16 by wnaiji            #+#    #+#             */
/*   Updated: 2023/09/25 16:48:57 by walidnaiji       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "parser.h"

int	is_builtin(char *str)
{
	if (ft_strncmp(str, "echo", 4) == 0)
		return (ECHO);
	else if (ft_strncmp(str, "cd", 2) == 0)
		return (CD);
	else if (ft_strncmp(str, "pwd", 3) == 0)
		return (PWD);
	else if (ft_strncmp(str, "export", 6) == 0)
		return (EXPORT);
	else if (ft_strncmp(str, "unset", 5) == 0)
		return (UNSET);
	else if (ft_strncmp(str, "env", 3) == 0)
		return (ENV);
	else if (ft_strncmp(str, "exit", 4) == 0)
		return (EXIT);
	else
		return (NO_BUILTIN);
}

char	**split_args(char *str)
{
	char	**args;

	if (!str)
		return NULL;
	args = ft_split(str, ' ');
	return (args);
}

char	*strtolower(char *str, int operator)
{
	int	i;

	i = 0;
	while (str[i] && operator == CMD)
	{
		str[i] = ft_tolower(str[i]);
		i++;
	}
	return (str);
}

t_input	input(t_lexer *lexer)
{
	t_lexer	*tmp;

	tmp = lexer;
	if (tmp->prev)
		tmp = tmp->prev;
	while (tmp->prev)
	{
		if (tmp->operator == INFILE || tmp->operator == HEREDOC)
			return (IN_FILE);
		else if (tmp->operator == PIPE)
			return (IN_PIPE);
		tmp = tmp->prev;
	}
	return (STDIN);
}

t_output	output(t_lexer *lexer)
{
	t_lexer	*tmp;

	tmp = lexer;
	if (tmp)
		tmp = tmp->next;
	while (tmp)
	{
		if (tmp->operator == OUTFILE || tmp->operator == OUTFILE_AP_MOD)
			return (OUT_FILE);
		else if (tmp->operator == PIPE)
			return (OUT_PIPE);
		tmp = tmp->next;
	}
	return (STDOUT);
}
