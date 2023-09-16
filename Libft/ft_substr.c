/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnaiji <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:44:06 by wnaiji            #+#    #+#             */
/*   Updated: 2022/11/13 02:42:19 by wnaiji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	ft_error(const char *s, unsigned int start)
{
	if (start > ft_strlen(s))
		return ('\0');
	else
		return ('1');
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*tmp;
	size_t	i;

	i = 0;
	if (!s || ft_error(s, start) == '\0')
	{
		tmp = malloc(sizeof(char));
		if (!(tmp))
			return (NULL);
		tmp[i] = '\0';
		return (tmp);
	}
	if (len > ft_strlen(s))
		len = ft_strlen(s) - start;
	tmp = malloc(sizeof(char) * (len + 1));
	if (!(tmp))
		return (NULL);
	while (i < len)
	{
		tmp[i] = s[start];
		start++;
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}
