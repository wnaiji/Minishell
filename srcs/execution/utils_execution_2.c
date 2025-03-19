/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_execution_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncardozo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 20:11:23 by ncardozo          #+#    #+#             */
/*   Updated: 2023/12/11 20:12:14 by ncardozo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_list_exec	*start_list(t_list_exec *list)
{
	t_list_exec	*tmp;

	tmp = list;
	while (tmp)
	{
		while (tmp->sublist && tmp->sublist->before)
			tmp->sublist = tmp->sublist->before;
		tmp = tmp->next;
	}
	return (list);
}

char	*ft_path(char **envp)
{
	int		i;
	char	*path;

	i = 0;
	path = NULL;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 4))
			path = ft_strdup(envp[i]);
		i++;
	}
	if (path)
		path = ft_strtrim(path, "PATH=");
	return (path);
}
