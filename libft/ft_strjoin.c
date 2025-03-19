/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncardozo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 15:33:59 by ncardozo          #+#    #+#             */
/*   Updated: 2023/11/15 10:01:45 by ncardozo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*s3;
	int		i;
	int		j;

	if (s1 && s2)
	{
		s3 = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
		if (s3 == NULL)
			return (NULL);
		i = -1;
		while (s1[++i])
			s3[i] = s1[i];
		i = -1;
		j = ft_strlen(s1);
		while (s2[++i])
		{
			s3[j] = s2[i];
			++j;
		}
		s3[j] = '\0';
		return (s3);
	}
	return (NULL);
}
