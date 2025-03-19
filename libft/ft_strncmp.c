/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncardozo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 15:18:03 by ncardozo          #+#    #+#             */
/*   Updated: 2023/11/02 21:08:35 by ncardozo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(char *s1, char *s2, int n)
{
	int		i;
	char	cmp_1;
	char	cmp_2;

	i = 0;
	if (!n)
		return (n);
	cmp_1 = (char)s1[i];
	cmp_2 = (char)s2[i];
	while ((cmp_1 && cmp_2) && (i < n))
	{
		cmp_1 = (char)s1[i];
		cmp_2 = (char)s2[i];
		if (cmp_1 != cmp_2)
			return (cmp_1 - cmp_2);
		++i;
	}
	return (cmp_1 - cmp_2);
}
