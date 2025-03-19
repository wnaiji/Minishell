/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walidnaiji <walidnaiji@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 22:35:55 by wnaiji            #+#    #+#             */
/*   Updated: 2023/12/12 21:21:07 by walidnaiji       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	swap_env(t_var_list **tmp)
{
	char	*tmp1;

	tmp1 = (*tmp)->name;
	(*tmp)->name = (*tmp)->next->name;
	(*tmp)->next->name = tmp1;
}

t_var_list	*sort_export(t_var_list *list)
{
	t_var_list	*tmp;
	int			index;

	tmp = list;
	index = 0;
	while (tmp)
	{
		if (tmp->next)
		{
			if (cmp_variable(tmp->name, tmp->next->name) == FALSE)
			{
				swap_env(&tmp);
				index = 1;
			}
		}
		tmp = tmp->next;
		if (!tmp && index == 1)
		{
			tmp = list;
			index = 0;
		}
	}
	return (list);
}

static void	join_quotes(t_var_list *tmp_list, char *name, char *value)
{
	char	*tmp_name;
	char	*tmp_value;
	char	*result;

	tmp_name = ft_strjoin(name, "\"");
	free(name);
	tmp_value = ft_strjoin(value, "\"");
	free(value);
	result = ft_strjoin(tmp_name, tmp_value);
	free(tmp_name);
	free(tmp_value);
	free(tmp_list->name);
	tmp_list->name = ft_strdup(result);
	free(result);
}

t_var_list	*double_quote_export(t_var_list *list)
{
	t_var_list	*tmp_list;
	int			i;
	char		*value;
	char		*name;

	tmp_list = list;
	while (tmp_list)
	{
		i = 0;
		if (ft_strchr(tmp_list->name, '=') != 0)
		{
			while (tmp_list->name[i++])
				if (tmp_list->name[i] == '=')
					break ;
			name = ft_substr(tmp_list->name, 0, i + 1);
			value = ft_substr(tmp_list->name, i + 1, ft_strlen(tmp_list->name));
			join_quotes(tmp_list, name, value);
		}
		tmp_list = tmp_list->next;
	}
	return (list);
}

void	print_export(t_var_list *list)
{
	t_var_list	*tmp;

	tmp = sort_export(list);
	tmp = double_quote_export(list);
	while (tmp)
	{
		printf("declare -x %s\n", tmp->name);
		tmp = tmp->next;
	}
}
