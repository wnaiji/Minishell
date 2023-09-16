/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnaiji <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 20:00:05 by wnaiji            #+#    #+#             */
/*   Updated: 2022/11/17 23:05:37 by wnaiji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_word(const char *s, const char c)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			j++;
			while (s[i] && s[i] != c)
				i++;
			i--;
		}
		i++;
	}
	return (j);
}

static size_t	ft_len_word(const char *s, const char c, size_t start)
{
	size_t	i;

	i = 0;
	while (s[start])
	{
		if (start == 0 && s[start] == c)
		{
			while (s[start] && s[start] == c)
				start++;
		}
		if (s[start] == c)
			break ;
		i++;
		start++;
	}
	return (i);
}

static char	*ft_malloc_str(const char *s, const char c, size_t start)
{
	size_t	i;
	size_t	len;
	char	*tmp;

	i = 0;
	len = ft_len_word(s, c, start);
	tmp = malloc(sizeof(char) * (len + 1));
	if (!tmp)
		return (NULL);
	while (s[start] && s[start] != c)
	{
		tmp[i] = s[start];
		i++;
		start++;
	}
	tmp[i] = '\0';
	return (tmp);
}

static size_t	ft_test(const char *s, const char c, size_t i)
{
	while (s[i] != c && s[i])
		i++;
	return (i);
}

char	**ft_split(const char *s, const char c)
{
	size_t	i;
	char	**tmp;
	size_t	j;

	if (!s)
		return (NULL);
	tmp = malloc(sizeof(char *) * (ft_count_word(s, c) + 1));
	if (!tmp)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			tmp[j] = ft_malloc_str(s, c, i);
			j++;
			i = ft_test(s, c, i);
			if (s[i] == '\0')
				break ;
		}
		i++;
	}
	tmp[j] = NULL;
	return (tmp);
}
