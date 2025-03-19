/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walidnaiji <walidnaiji@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 16:08:55 by ncardozo          #+#    #+#             */
/*   Updated: 2023/12/13 14:51:32 by walidnaiji       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	is_valid_variable(char *arg)
{
	int	i;

	i = 0;
	g_sig = 1;
	if (ft_isdigit(arg[i]) == 1 || arg[0] == '\0')
	{
		put_error(arg);
		return (FALSE);
	}
	while (arg[i] && arg[i] != '=')
	{
		if (ft_isalnum(arg[i]) == 0 && arg[i] != '_')
		{
			put_error(arg);
			return (FALSE);
		}
		i++;
	}
	if (i > 30)
	{
		put_error(arg);
		return (FALSE);
	}
	g_sig = 0;
	return (TRUE);
}

static int	check_variable_exists(t_var_list *list, char *arg)
{
	char	*tmp_name;
	char	*tmp_arg;
	int		len;
	int		i;

	i = 0;
	tmp_name = NULL;
	tmp_arg = NULL;
	len = 0;
	while (list->name[i] && list->name[i++] != '=')
		len++;
	tmp_name = ft_substr(list->name, 0, len);
	i = 0;
	len = 0;
	while (arg[i] && arg[i++] != '=')
		len++;
	tmp_arg = ft_substr(arg, 0, len);
	if (ft_strncmp(tmp_name, tmp_arg, ft_strlen(tmp_arg) + 1) == 0)
	{
		(free(tmp_arg), free(tmp_name));
		return (TRUE);
	}
	(free(tmp_arg), free(tmp_name));
	return (FALSE);
}

void	new_value_variable(t_var_list *list, char *str)
{
	char	*tmp;
	char	*tmp_free;

	tmp = ft_strdup(str);
	tmp_free = list->name;
	list->name = tmp;
	free(tmp_free);
}

t_var_list	*init_list_export(char **args, t_var_list	*list)
{
	int			i;
	t_var_list	*list_tmp;

	i = 0;
	while (args[++i])
	{
		list_tmp = list;
		while (list_tmp)
		{
			if (is_valid_variable(args[i]) == FALSE)
				break ;
			if (check_variable_exists(list_tmp, args[i]) == TRUE)
			{
				new_value_variable(list_tmp, args[i]);
				break ;
			}
			else if (!list_tmp->next)
			{
				list = list_export_add_back_list(list, args[i]);
				break ;
			}
			list_tmp = list_tmp->next;
		}
	}
	return (list);
}

void	export_builtin(char **args, t_tools *tools)
{
	t_var_list	*list;
	int			i;

	i = 0;
	list = NULL;
	while (tools->env[i])
		list = list_export_add_back_list(list, tools->env[i++]);
	list = init_list_export(args, list);
	if (args[1] == NULL)
	{
		print_export(list);
		g_sig = 0;
	}
	else
	{
		free_env(tools->env);
		tools->env = stock_new_env(list);
	}
	while (list)
		list = delete_node_export(list);
}
