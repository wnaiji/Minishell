/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_spaces.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncardozo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 07:53:51 by ncardozo          #+#    #+#             */
/*   Updated: 2023/10/27 12:14:06 by ncardozo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_space(char c)
{
	return (c == 32 || c == 9);
}

static void	remove_spaces_loop(char **str, char **tmp, \
							int *iter_src, int *iter_dst)
{
	while ((*tmp)[*iter_src])
	{
		if ((is_space((*tmp)[*iter_src]) == 0) || \
				(is_space((*tmp)[*iter_src]) == 1 \
			&& is_space((*tmp)[*iter_src + 1]) == 0))
		{
			(*str)[*iter_dst] = (*tmp)[*iter_src];
			++(*iter_dst);
			++(*iter_src);
		}
		else
			++(*iter_src);
	}
}

char	*remove_spaces(char *str)
{
	int		iter_src;
	int		iter_dst;
	int		str_len;
	char	*tmp;

	iter_src = 0;
	iter_dst = 0;
	str_len = ft_strlen(str);
	tmp = strdup(str);
	str = NULL;
	str = malloc(sizeof(char) * str_len + 1);
	if (!str)
		return (NULL);
	remove_spaces_loop(&str, &tmp, &iter_src, &iter_dst);
	free(tmp);
	tmp = NULL;
	str[iter_dst] = '\0';
	return (str);
}
