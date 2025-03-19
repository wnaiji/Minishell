/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncardozo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 12:24:36 by ncardozo          #+#    #+#             */
/*   Updated: 2023/11/01 12:25:34 by ncardozo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	is_a_separator(char to_check)
{
	if (ft_strchr(SEPARATORS, to_check) != 0)
		return (to_check);
	else
		return (0);
}

void	search_type_of_quote(t_tools *tools)
{
	if (tools->command_line[tools->iter] == SIMPLE_QUOTE)
		tools->quote_type = TOKEN_BT_SIMPLE_QUOTES;
	else
		tools->quote_type = TOKEN_BT_DOUBLE_QUOTES;
}
