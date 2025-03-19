/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_fonctions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncardozo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 15:46:28 by ncardozo          #+#    #+#             */
/*   Updated: 2023/11/28 23:26:45 by ncardozo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	replace_token_word(t_node *actual_list, char *new_data)
{
	free(actual_list->data);
	actual_list->data = ft_strdup(new_data);
}

int	dollar_chr(char *data)
{
	int		iter;
	int		dollar_count;

	iter = -1;
	dollar_count = 0;
	while (data[++iter])
	{
		if (data[iter] == DOLLAR_CHAR)
			++dollar_count;
	}
	return (dollar_count);
	return (0);
}

int	count_dollars(const char **pos)
{
	int	count;

	count = 0;
	while (**pos == '$')
	{
		count++;
		(*pos)++;
	}
	return (count);
}
