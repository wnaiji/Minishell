/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walidnaiji <walidnaiji@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 20:03:03 by wnaiji            #+#    #+#             */
/*   Updated: 2023/07/02 14:07:39 by walidnaiji       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}

void	ft_close(t_arg arg)
{
	close(arg.fd[0]);
	close(arg.fd[1]);
	close(arg.fd_in);
	close(arg.fd_out);
}

void	ft_error(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

t_arg	init_arg_pipex(int argc, char **argv, char **envp, t_arg arg)
{
	arg.cmd1 = parsing_cmd(argv[2]);
	arg.cmd2 = parsing_cmd(argv[argc - 2]);
	arg.env = ft_envp(envp);
	arg.fd_in = open_fd(argv[1]);
	arg.fd_out = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (arg.fd_out == -1)
		perror("Error: open STDOUT\n");
	arg.nb = 1;
	arg.h_d = 0;
	return (arg);
}

t_arg	init_arg_here_doc(int argc, char **argv, char **envp, t_arg arg)
{
	arg.cmd1 = parsing_cmd(argv[3]);
	arg.cmd2 = parsing_cmd(argv[argc - 2]);
	arg.env = ft_envp(envp);
	unlink(".here_doc");
	arg.fd_in = open(".here_doc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	arg.fd_out = open(argv[argc - 1], O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (arg.fd_out == -1)
		perror("Error: open STDOUT\n");
	arg.nb = 2;
	arg.h_d = 1;
	return (arg);
}
