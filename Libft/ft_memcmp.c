/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnaiji <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 12:09:26 by wnaiji            #+#    #+#             */
/*   Updated: 2022/11/13 00:11:30 by wnaiji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*buf_s1;
	unsigned char	*buf_s2;
	size_t			i;

	buf_s1 = (unsigned char *)s1;
	buf_s2 = (unsigned char *)s2;
	i = 0;
	while (i < n && buf_s1[i] == buf_s2[i])
		i++;
	if (i == n)
		return (0);
	else
		return (buf_s1[i] - buf_s2[i]);
}
