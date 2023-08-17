/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walidnaiji <walidnaiji@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 20:04:15 by wnaiji            #+#    #+#             */
/*   Updated: 2023/07/02 14:02:38 by walidnaiji       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	whild_one(t_arg arg)
{
	int		i;
	char	*str;

	i = 0;
	if (arg.fd_in == -1)
		exit(EXIT_FAILURE);
	(dup2(arg.fd_in, STDIN_FILENO), dup2(arg.fd[1], STDOUT_FILENO));
	ft_close(arg);
	while (arg.env[i])
	{
		str = ft_ft_strjoin(arg.env[i], arg.cmd1[0]);
		if (execve(arg.cmd1[0], arg.cmd1, arg.env) == -1)
		{
			if (access(str, X_OK) == 0)
			{
				execve(str, arg.cmd1, arg.env);
				ft_error("Erreur: execve\n");
			}
			free(str);
			i++;
		}
	}
	dup2(2, STDOUT_FILENO);
	ft_printf("command not found\n");
	exit(EXIT_FAILURE);
}

void	whild_last(t_arg arg)
{
	int		i;
	char	*str;

	i = 0;
	dup2(arg.fd_in, STDIN_FILENO);
	dup2(arg.fd_out, STDOUT_FILENO);
	ft_close(arg);
	while (arg.env[i])
	{
		str = ft_ft_strjoin(arg.env[i], arg.cmd2[0]);
		if (execve(arg.cmd2[0], arg.cmd2, arg.env) == -1)
		{
			if (access(str, X_OK) == 0)
			{
				execve(str, arg.cmd2, arg.env);
				ft_error("Erreur: execve\n");
			}
			free(str);
			i++;
		}
	}
	dup2(2, STDOUT_FILENO);
	ft_printf("command not found\n");
	exit(EXIT_FAILURE);
}

void	pipex(int argc, char **argv, t_arg arg)
{
	while (++arg.nb <= argc - 3)
	{
		(ft_free(arg.cmd1), arg.cmd1 = parsing_cmd(argv[arg.nb]));
		if (arg.nb > 2 && arg.h_d == 0)
		{
			(close(arg.fd_in), arg.fd_in = dup(arg.fd[0]));
			(close(arg.fd[0]), close(arg.fd[1]));
		}
		if (pipe(arg.fd) == -1)
			ft_error("Error: pipe\n");
		arg.pid1 = fork();
		if (arg.pid1 < 0)
			ft_error("Error: fork pid1\n");
		if (arg.pid1 == 0)
			whild_one(arg);
		arg.h_d = 0;
		waitpid(arg.pid1, NULL, WNOHANG);
	}
	((close(arg.fd_in), arg.fd_in = dup(arg.fd[0])), arg.pid2 = fork());
	if (arg.pid2 < 0)
		ft_error("Error: fork pid2\n");
	if (arg.pid2 == 0)
		whild_last(arg);
	(ft_close(arg), waitpid(arg.pid2, NULL, 0));
	(ft_free(arg.env), ft_free(arg.cmd1), ft_free(arg.cmd2));
}

int	main(int argc, char **argv, char **envp)
{
	t_arg	arg;

	arg.cmd1 = NULL;
	if (!ft_strncmp(argv[1], "here_doc", 9))
	{
		arg = init_arg_here_doc(argc, argv, envp, arg);
		here_doc(argc, argv, arg);
	}
	else if (argc > 4)
	{
		arg = init_arg_pipex(argc, argv, envp, arg);
		pipex(argc, argv, arg);
	}
	else
	{
		ft_printf("Error: The number of argument is not correct\n");
		exit(EXIT_FAILURE);
	}
	return (0);
}
