/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncardozo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 12:52:11 by ncardozo          #+#    #+#             */
/*   Updated: 2023/12/05 19:47:01 by ncardozo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_lstsize(t_node *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

int	two_d_array_size(char **envp)
{
	int	count;

	count = 0;
	while (envp[count])
		++count;
	return (count);
}

t_tools	*initialise_tools(t_tools *tools)
{
	tools = malloc(sizeof(t_tools));
	tools->command_line = NULL;
	tools->env = NULL;
	tools->pos = NULL;
	tools->temp_pos = NULL;
	tools->result = NULL;
	tools->out = NULL;
	tools->data = NULL;
	tools->quote_type = 0;
	tools->actual_sep = 0;
	tools->iter = 0;
	tools->string_len = 0;
	tools->quotes_count = -1;
	return (tools);
}
