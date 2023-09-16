/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnaiji <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 11:42:14 by wnaiji            #+#    #+#             */
/*   Updated: 2022/11/13 00:12:56 by wnaiji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*buf_dest;
	unsigned char	*buf_src;
	size_t			i;

	if (!dest && !src)
		return (0);
	buf_dest = (unsigned char *)dest;
	buf_src = (unsigned char *)src;
	i = 0;
	if (src < dest)
	{
		while (n-- > i)
			buf_dest[n] = buf_src[n];
	}
	else
	{
		while (i < n)
		{
			buf_dest[i] = buf_src[i];
			i++;
		}
	}
	return (dest);
}
