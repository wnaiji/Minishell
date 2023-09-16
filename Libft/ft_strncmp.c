/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnaiji <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:57:58 by wnaiji            #+#    #+#             */
/*   Updated: 2022/11/13 00:44:50 by wnaiji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*buf_s1;
	unsigned char	*buf_s2;
	size_t			i;

	i = 0;
	buf_s1 = (unsigned char *)s1;
	buf_s2 = (unsigned char *)s2;
	if (n == 0)
		return (0);
	while (buf_s1[i] && buf_s2[i] && buf_s1[i] == buf_s2[i] && i < n - 1)
		i++;
	return (buf_s1[i] - buf_s2[i]);
}
