/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncardozo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 15:17:11 by ncardozo          #+#    #+#             */
/*   Updated: 2023/11/14 23:13:26 by ncardozo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	ft_strchr(const char *s, char c)
{
	char	*str;

	str = (char *)s;
	while (*str != c && *str)
		++str;
	if (*str == c)
		return (*str);
	else
		return (0);
	return (0);
}
