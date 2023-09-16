/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnaiji <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 11:20:35 by wnaiji            #+#    #+#             */
/*   Updated: 2022/11/17 00:12:58 by wnaiji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	beg_trim(const char *s, const char *set)
{
	int	i;
	int	j;

	i = 0;
	while (s[i])
	{
		j = 0;
		while (set[j])
		{
			if (s[i] == set[j])
				break ;
			j++;
			if (set[j] == '\0')
				return (i);
		}
		i++;
	}
	return (0);
}

static int	end_trim(const char *s, const char *set)
{
	int	i;
	int	len;

	len = ft_strlen(s);
	while (len > 0)
	{
		i = 0;
		while (set[i])
		{
			if (s[len - 1] == set[i])
				break ;
			i++;
			if (set[i] == '\0')
				return (len = ft_strlen(s) - len);
		}
		len--;
	}
	return (0);
}

static char	*ft_s_null(void)
{
	char	*tmp;

	tmp = malloc(sizeof(char));
	if (!tmp)
		return (NULL);
	tmp[0] = '\0';
	return (tmp);
}

static int	boolean_0_trim(const char *s, const char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == s[0])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(const char *s, const char *set)
{
	int		i;
	int		beg;
	int		end;
	int		len_tmp;
	char	*tmp;

	if (!s || !set)
		return (0);
	i = 0;
	beg = beg_trim(s, set);
	end = end_trim(s, set);
	len_tmp = ft_strlen(s) - beg - end;
	if (beg == 0 && end == 0 && set[0] != '\0' && boolean_0_trim(s, set) == 1)
		return (tmp = ft_s_null());
	tmp = malloc(sizeof(char) * (ft_strlen(s) - beg - end + 1));
	if (!tmp)
		return (NULL);
	while (i < len_tmp)
	{
		tmp[i] = s[beg];
		i++;
		beg++;
	}
	tmp[i] = '\0';
	return (tmp);
}
