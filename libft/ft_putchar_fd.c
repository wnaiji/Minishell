/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncardozo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 15:25:17 by ncardozo          #+#    #+#             */
/*   Updated: 2023/12/11 21:03:43 by ncardozo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	ssize_t	ret;

	if (fd)
	{
		ret = write(fd, &c, 1);
		if (ret == -1)
		{
			perror("write() error");
			return ;
		}
	}
}
