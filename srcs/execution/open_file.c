/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncardozo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 17:02:13 by wnaiji            #+#    #+#             */
/*   Updated: 2023/12/12 23:37:11 by ncardozo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	open_infile(char *str, t_list_exec *list)
{
	int	fd;

	fd = open(str, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		perror(str);
		if (!(ft_listsize(list) == 1
				&& last_token(list->sublist) != NO_BUILTIN))
			exit(1);
		g_sig = 1;
	}
	return (fd);
}

int	open_outfile(char *str, t_list_exec *list)
{
	int	fd;

	fd = open(str, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		perror(str);
		if (!(ft_listsize(list) == 1
				&& last_token(list->sublist) != NO_BUILTIN))
			exit(1);
		g_sig = 1;
	}
	return (fd);
}

int	open_ap_mod(char *str, t_list_exec *list)
{
	int	fd;

	fd = open(str, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		perror(str);
		if (!(ft_listsize(list) == 1
				&& last_token(list->sublist) != NO_BUILTIN))
			exit(1);
		g_sig = 1;
	}
	return (fd);
}

t_list_exec	*open_file(t_list_exec *list)
{
	t_sublist	*subtmp;

	subtmp = list->sublist;
	while (subtmp)
	{
		if (subtmp->tok == INFILE)
			list->fd_in = open_infile(subtmp->str[0], list);
		else if (subtmp->tok == OUTFILE)
			list->fd_out = open_outfile(subtmp->str[0], list);
		else if (subtmp->tok == AP_MOD)
			list->fd_out = open_ap_mod(subtmp->str[0], list);
		subtmp = subtmp->next;
	}
	return (list);
}
