/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncardozo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 14:29:18 by wnaiji            #+#    #+#             */
/*   Updated: 2023/12/11 20:12:05 by ncardozo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**env_path(char **path, t_tools *tools)
{
	char	*str;
	int		i;

	i = 0;
	str = ft_path(tools->env);
	if (!str)
		return (NULL);
	path = ft_split(str, ':');
	free(str);
	while (path[i])
	{
		str = ft_strjoin(path[i], "/");
		free(path[i]);
		path[i] = ft_strdup(str);
		free(str);
		i++;
	}
	return (path);
}

t_builtin	last_token(t_sublist *sublist)
{
	t_sublist	*subtmp;

	subtmp = sublist;
	if (!sublist)
		return (0);
	while (subtmp->next)
		subtmp = subtmp->next;
	if (subtmp->tok != CMD)
		return (0);
	return (subtmp->builtin);
}

char	**last_content(t_sublist *sublist)
{
	t_sublist	*subtmp;

	subtmp = sublist;
	if (!sublist)
		return (0);
	while (subtmp->next)
		subtmp = subtmp->next;
	if (subtmp->tok != CMD)
		return (NULL);
	return (subtmp->str);
}

int	ft_listsize(t_list_exec *lst)
{
	int			i;
	t_list_exec	*tmp;

	i = 0;
	tmp = lst;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}
