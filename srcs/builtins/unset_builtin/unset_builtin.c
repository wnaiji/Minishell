/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncardozo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 18:49:46 by ncardozo          #+#    #+#             */
/*   Updated: 2023/12/12 23:22:35 by ncardozo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	put_error_unset(char *arg)
{
	ft_putstr_fd("minishell: unset: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd(": not a valid identifier", 2);
	g_sig = 127;
}

static int	is_valid_variable(char *arg)
{
	int	i;

	i = 0;
	if (ft_isdigit(arg[i]) == 1 || arg[0] == '\0')
	{
		put_error(arg);
		return (FALSE);
	}
	while (arg[i])
	{
		if (ft_isalnum(arg[i]) == 0 && arg[i] != '_')
		{
			put_error_unset(arg);
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

int	check_variable_exists(t_var_list *list, char *arg)
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

t_var_list	*unset_variable(char **args, t_var_list *list)
{
	t_var_list	*tmp;
	int			i;

	i = 0;
	while (args[i])
	{
		tmp = list;
		while (tmp)
		{
			if (is_valid_variable(args[i]) == FALSE)
				break ;
			else if (check_variable_exists(tmp, args[i]) == TRUE)
				tmp = delete_node_export(tmp);
			else
				tmp = tmp->next;
		}
		i++;
	}
	return (list);
}

void	unset_builtin(char **args, t_tools *tools)
{
	t_var_list	*list;
	int			i;

	i = 0;
	list = NULL;
	while (tools->env[i])
		list = list_export_add_back_list(list, tools->env[i++]);
	list = unset_variable(args, list);
	free_env(tools->env);
	tools->env = stock_new_env(list);
	while (list)
		list = delete_node_export(list);
}
