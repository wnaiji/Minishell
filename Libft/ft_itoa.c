/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnaiji <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 15:21:40 by wnaiji            #+#    #+#             */
/*   Updated: 2022/11/17 13:17:36 by wnaiji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_size_malloc(int n)
{
	int	size;

	size = 0;
	if (n < 0)
	{
		size++;
		n *= -1;
	}
	while (n >= 1)
	{
		n = n / 10;
		size++;
	}
	return (size);
}

static char	*ft_null_max(int n)
{
	char	*tmp;
	char	*nb;
	int		i;

	nb = "-2147483648\0";
	i = 0;
	if (n == 0)
	{
		tmp = malloc(sizeof(char) * 2);
		tmp[0] = '0';
		tmp[1] = '\0';
		return (tmp);
	}
	tmp = malloc(sizeof(char) + 12);
	if (!tmp)
		return (NULL);
	while (nb[i])
	{
		tmp[i] = nb[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

static char	*ft_strrev(char *str)
{
	char	tmp;
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(str) - 1;
	if (str[i] == '-')
		i++;
	while (len >= i)
	{
		tmp = str[i];
		str[i] = str[len];
		str[len] = tmp;
		i++;
		len--;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char	*tmp;
	int		i;

	i = 0;
	if (n == -2147483648 || n == 0)
		return (tmp = ft_null_max(n));
	tmp = malloc(sizeof(char) * (ft_size_malloc(n) + 1));
	if (!tmp)
		return (NULL);
	if (n < 0)
	{
		n *= -1;
		tmp[i++] = '-';
	}
	while (n >= 1)
	{
		tmp[i++] = n % 10 + '0';
		n /= 10;
	}
	tmp[i++] = '\0';
	return (tmp = ft_strrev(tmp));
}
