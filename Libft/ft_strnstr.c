/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnaiji <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 18:04:54 by wnaiji            #+#    #+#             */
/*   Updated: 2022/11/13 01:38:21 by wnaiji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (s2[0] == '\0' || (!s1 && n == 0))
		return ((char *)s1);
	while (s1[i] && n != 0)
	{
		j = 0;
		if (s1[i] == s2[j])
		{
			while (s1[i] && s2[j] && s1[i] == s2[j] && i < n)
			{
				i++;
				j++;
			}
			if (s2[j] == '\0')
				return ((char *)s1 + (i - j));
			i -= j;
		}
		i++;
	}
	return (NULL);
}
