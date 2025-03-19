/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walidnaiji <walidnaiji@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 10:49:34 by wnaiji            #+#    #+#             */
/*   Updated: 2023/12/13 14:14:00 by walidnaiji       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	result_here_doc(int hd_fd, char *limiter, t_tools *tools)
{
	char	*tmp;

	if (!limiter)
	{
		ft_putendl_fd("minishell: syntax error near \
unexpected token `newline'", STDERR_FILENO);
		exit(1);
	}
	signal_mode_handling(HEREDOC_MODE);
	while (1)
	{
		tmp = readline("> ");
		if (!tmp)
		{
			printf("\r> ");
			break ;
		}
		if (!ft_strncmp(tmp, limiter, ft_strlen(tmp) + 1))
			break ;
		tmp = expander_heredoc(tmp, tools);
		ft_putendl_fd(tmp, hd_fd);
		free(tmp);
	}
	free(tmp);
	close(hd_fd);
	return (hd_fd);
}

static void	execute_result_here_doc(t_list_exec *tmp, t_sublist *subtmp)
{
	if (!tmp || !subtmp)
		return ;
	tmp->hd_fd[1] = result_here_doc(tmp->hd_fd[1], subtmp->str[0], tmp->tools);
}

static void	process_sublist(t_list_exec *tmp)
{
	t_sublist	*subtmp;

	subtmp = tmp->sublist;
	while (subtmp)
	{
		if (subtmp->tok == HERE_DOC)
		{
			if (pipe(tmp->hd_fd) == -1)
			{
				perror("minishell: pipe");
				break ;
			}
			execute_result_here_doc(tmp, subtmp);
		}
		subtmp = subtmp->next;
	}
}

t_list_exec	*here_doc(t_list_exec *list)
{
	t_list_exec	*tmp;

	tmp = list;
	signal_mode_handling(HEREDOC_MODE);
	while (tmp)
	{
		process_sublist(tmp);
		tmp = tmp->next;
	}
	return (list);
}
