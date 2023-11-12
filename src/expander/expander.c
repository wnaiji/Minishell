/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walidnaiji <walidnaiji@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 14:29:39 by wnaiji            #+#    #+#             */
/*   Updated: 2023/11/12 14:14:35 by walidnaiji       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

t_lexer	expander_by_lexer(t_lexer *lexer)
{
	t_lexer	*tmp;
	char	*new_str;

	tmp = lexer;
	new_str = NULL;
	while (tmp)
	{
		if (tmp->operator == NO_OPERATOR && tmp->quoted != SIMPLE_QUOTED
			&& ft_strchr(tmp->str, EXPAND) != NULL)
		{
			new_str = expander(tmp->str);
			free(tmp->str);
			tmp->str = ft_strdup(new_str);
			free(new_str);
		}
		tmp = tmp->next;
	}
	return (lexer);
}

char	*expander(char *str)
{
	int		index;
	int		len;
	int		start;
	char	*expand;
	char	*new_value:
	char	*tmp;

	index = 0;
	start = start_expand(str, index);
	len = len_expand(str, start);
	expand = ft_substr(str, start, len);
	new_value = getenv(expand);
	if (!new)
	{
		/*modifier la valeur de expand*/
		/*voir pour faire l'expander de la même manière que pour printf*/
		/*si lexpander rend une str vide, retourner directement sur le prompt*/
	}
}
