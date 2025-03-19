/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walidnaiji <walidnaiji@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 18:33:33 by ncardozo          #+#    #+#             */
/*   Updated: 2023/12/13 14:18:56 by walidnaiji       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	infile(t_list_exec *list)
{
	int			fd_in;
	t_sublist	*subtmp;

	fd_in = 0;
	subtmp = list->sublist;
	while (subtmp)
	{
		if (subtmp->tok == INFILE)
			fd_in = dup(list->fd_in);
		else if (subtmp->tok == HERE_DOC)
		{
			fd_in = dup(list->hd_fd[0]);
			//close(list->hd_fd[0]);
		}
		subtmp = subtmp->next;
	}
	if (fd_in == 0 && list->before)
	{
		fd_in = dup(list->before->p_fd[0]);
		close(list->before->p_fd[0]);
	}
	else if (fd_in == 0)
		fd_in = dup(STDIN_FILENO);
	return (fd_in);
}

int	outfile(t_list_exec *list)
{
	int			fd_out;
	t_sublist	*subtmp;

	fd_out = 0;
	subtmp = list->sublist;
	while (subtmp)
	{
		if (subtmp->tok == OUTFILE || subtmp->tok == AP_MOD)
			fd_out = dup(list->fd_out);
		subtmp = subtmp->next;
	}
	if (fd_out == 0 && list->next)
	{
		fd_out = dup(list->p_fd[1]);
		close(list->p_fd[1]);
	}
	else if (fd_out == 0)
		fd_out = dup(STDOUT_FILENO);
	return (fd_out);
}

void	wild_exec(t_list_exec *list, char **path)
{
	char	**cmd;
	int		i;
	char	*str;

	i = 0;
	cmd = last_content(list->sublist);
	if (!cmd)
		exit(EXIT_SUCCESS);
	dup2(list->p_fd[0], STDIN_FILENO);
	dup2(list->p_fd[1], STDOUT_FILENO);
	close(list->p_fd[0]);
	close(list->p_fd[1]);
	execve(cmd[0], cmd, list->tools->env);
	while (path && path[i])
	{
		str = ft_strjoin(path[i], cmd[0]);
		execve(str, cmd, list->tools->env);
		free(str);
		i++;
	}
	dup2(STDERR_FILENO, STDOUT_FILENO);
	if (errno != EACCES)
		printf("minishell: %s: command not found\n", cmd[0]);
	exit(127);
}

void	cmd_builtin(t_list_exec *list)
{
	int	tok_built;

	tok_built = last_token(list->sublist);
	dup2(list->p_fd[0], STDIN_FILENO);
	dup2(list->p_fd[1], STDOUT_FILENO);
	close(list->p_fd[0]);
	close(list->p_fd[1]);
	if (tok_built == ECHO)
		echo_builtin(last_content(list->sublist));
	else if (tok_built == PWD)
		pwd_builtin(last_content(list->sublist));
	else if (tok_built == ENV)
		env_builtin(list->tools, last_content(list->sublist));
	else if (tok_built == EXPORT && ft_listsize(list) > 1)
		export_builtin(last_content(list->sublist), list->tools);
	else if (tok_built == EXIT)
		exit_builtin(last_content(list->sublist));
	else if (tok_built == CD && ft_listsize(list) == 1)
		cd_builtin(last_content(list->sublist), list->tools->env);
	else if (tok_built == EXPORT && ft_listsize(list) == 1)
		export_builtin(last_content(list->sublist), list->tools);
	else if (tok_built == UNSET)
		unset_builtin(last_content(list->sublist), list->tools);
}
