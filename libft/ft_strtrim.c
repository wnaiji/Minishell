/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncardozo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 15:30:33 by ncardozo          #+#    #+#             */
/*   Updated: 2023/11/14 13:17:44 by ncardozo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_setcheck(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i++] == c)
			return (1);
	}
	return (0);
}

static int	ft_strtrim_loop(char **str, char **s1, int *start, int *end)
{
	int	iter;

	iter = 0;
	while ((*start) < (*end))
	{
		(*str)[iter] = (*s1)[*start];
		++iter;
		++(*start);
	}
	return (iter);
}

char	*ft_strtrim(char *s1, char *set)
{
	char	*str;
	int		start;
	int		end;
	int		i;

	start = 0;
	if (s1 == 0 || set == 0)
		return (0);
	end = ft_strlen(s1);
	while (s1[start] && ft_setcheck(s1[start], set))
		++start;
	while (end > start && ft_setcheck(s1[end - 1], set))
		--end;
	str = malloc(sizeof(char) * (end - start + 1));
	if (!str)
		return (0);
	i = ft_strtrim_loop(&str, &s1, &start, &end);
	free(s1);
	s1 = NULL;
	str[i] = '\0';
	return (str);
}
