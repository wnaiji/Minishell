/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnaiji <wnaiji@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 22:15:59 by wnaiji            #+#    #+#             */
/*   Updated: 2023/07/01 16:33:39 by wnaiji           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	here_doc(int argc, char **argv, t_arg arg)
{
	char	*str;
	char	*limiter;

	limiter = ft_ft_strjoin(argv[2], "\n");
	while (1)
	{
		ft_putstr_fd("> ", STDOUT_FILENO);
		str = get_next_line(STDIN_FILENO);
		if (!ft_strncmp(str, limiter, ft_strlen(str)))
			break ;
		ft_putstr_fd(str, arg.fd_in);
		free(str);
	}
	free(limiter);
	free(str);
	close(arg.fd_in);
	arg.fd_in = open(".here_doc", O_RDONLY);
	pipex(argc, argv, arg);
	unlink(".here_doc");
}
