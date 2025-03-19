/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncardozo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 12:19:27 by ncardozo          #+#    #+#             */
/*   Updated: 2023/11/04 12:19:32 by ncardozo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_itoa_util(long *nb, int *neg, int *tmp)
{
	if ((*nb) < 0)
	{
		(*nb) = -(*nb);
		(*neg) = -1;
		(*tmp)++;
	}
	while ((*nb))
	{
		(*nb) /= 10;
		(*tmp)++;
	}
}

char	*ft_itoa(int n)
{
	char	*ret;
	long	nb;
	int		neg;
	int		tmp;

	nb = (long)n;
	neg = 1;
	tmp = 0;
	if (nb == 0)
		return (ft_strdup("0"));
	ft_itoa_util(&nb, &neg, &tmp);
	nb = (long)n * neg;
	ret = malloc(sizeof(char) * tmp + 1);
	if (!ret)
		return (NULL);
	ret[tmp] = 0;
	while ((tmp - 1) >= 0)
	{
		ret[tmp - 1] = (nb % 10) + 48;
		nb /= 10;
		tmp--;
	}
	if (neg == -1)
		ret[0] = '-';
	return (ret);
}
