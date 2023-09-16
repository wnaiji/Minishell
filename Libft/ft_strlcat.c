/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnaiji <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 18:22:35 by wnaiji            #+#    #+#             */
/*   Updated: 2022/11/13 03:07:12 by wnaiji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	len_dest;

	i = 0;
	if (!size || (!dest && !size))
		return (ft_strlen(src));
	len_dest = ft_strlen(dest);
	j = 0;
	while (dest[i] && i < size)
		i++;
	while (src[j] && i < size - 1)
	{
		dest[i] = src[j];
		j++;
		i++;
	}
	if (size >= len_dest)
		dest[i] = '\0';
	if (size < len_dest)
		return (ft_strlen(src) + size);
	else
		return (ft_strlen(src) + len_dest);
}
