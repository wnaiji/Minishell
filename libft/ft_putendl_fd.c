/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walidnaiji <walidnaiji@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 15:27:20 by ncardozo          #+#    #+#             */
/*   Updated: 2023/12/11 09:29:49 by walidnaiji       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	ssize_t	ret;

	if (fd < 0)
		return ;
	if (!s)
		return ;
	ft_putstr_fd(s, fd);
	ret = write(fd, "\n", 1);
	if (ret == -1)
	{
		perror("write() error");
		return ;
	}
}
