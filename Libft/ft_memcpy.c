/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnaiji <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 11:34:29 by wnaiji            #+#    #+#             */
/*   Updated: 2022/11/12 23:22:23 by wnaiji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*buf_dest;
	unsigned char	*buf_src;
	size_t			i;

	if (!dest && !src)
		return (0);
	i = 0;
	buf_dest = (unsigned char *)dest;
	buf_src = (unsigned char *)src;
	while (i < n)
	{
		buf_dest[i] = buf_src[i];
		i++;
	}
	return ((void *)dest);
}
