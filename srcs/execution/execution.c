/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walidnaiji <walidnaiji@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 16:33:05 by wnaiji            #+#    #+#             */
/*   Updated: 2023/12/13 14:22:10 by walidnaiji       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	cmd_one_builtin(t_list_exec *tmp)
{
	tmp = here_doc(tmp);
	tmp = open_file(tmp);
	tmp->p_fd[0] = infile(tmp);
	tmp->p_fd[1] = outfile(tmp);
	tmp->stdout_copy = dup(STDOUT_FILENO);
	dup2(tmp->p_fd[1], STDOUT_FILENO);
	if (tmp->p_fd[0] > 0 && tmp->p_fd[1] > 0)
	{
		if (last_token(tmp->sublist) == ECHO)
			echo_builtin(last_content(tmp->sublist));
		else if (last_token(tmp->sublist) == PWD)
			pwd_builtin(last_content(tmp->sublist));
		else if (last_token(tmp->sublist) == ENV)
			env_builtin(tmp->tools, last_content(tmp->sublist));
		else if (last_token(tmp->sublist) == EXIT)
			exit_builtin(last_content(tmp->sublist));
		else if (last_token(tmp->sublist) == CD)
			cd_builtin(last_content(tmp->sublist), tmp->tools->env);
		else if (last_token(tmp->sublist) == EXPORT)
			export_builtin(last_content(tmp->sublist), tmp->tools);
		else if (last_token(tmp->sublist) == UNSET)
			unset_builtin(last_content(tmp->sublist), tmp->tools);
		dup2(tmp->stdout_copy, STDOUT_FILENO);
	}
}

void	close_wait(t_list_exec *list)
{
	t_list_exec	*tmp;
	int			exit;

	tmp = list;
	while (tmp)
	{
		close(tmp->p_fd[0]);
		close(tmp->p_fd[1]);
		tmp = tmp->next;
	}
	tmp = list;
	while (tmp)
	{
		waitpid(tmp->pid, &exit, 0);
		tmp = tmp->next;
		if (!(ft_listsize(list) == 1 && \
		last_token(list->sublist) != NO_BUILTIN))
			g_sig = WEXITSTATUS(exit);
	}
}

void	init_redirection(t_list_exec **tmp)
{
	//*list = here_doc(*list);
	*tmp = open_file(*tmp);
	close((*tmp)->p_fd[0]);
	(*tmp)->p_fd[0] = infile(*tmp);
	(*tmp)->p_fd[1] = outfile(*tmp);
}

void	exec_loop(t_list_exec *list, t_list_exec *tmp, char **path)
{
	if (pipe(tmp->p_fd) == -1)
	{
		perror("minishell: pipe");
		return ;
	}
	if (ft_listsize(list) > 1 || (ft_listsize(list) == 1
			&& last_token(list->sublist) == NO_BUILTIN))
		tmp->pid = fork();
	if (tmp->pid == -1)
	{
		perror("minishell: fork");
		return ;
	}
	else if (tmp->pid == 0 && (ft_listsize(list) > 1 || \
		(ft_listsize(list) == 1 && last_token(list->sublist) == NO_BUILTIN)))
	{
		init_redirection(&tmp);
		if (last_token(tmp->sublist) == NO_BUILTIN)
			wild_exec(tmp, path);
		else
			cmd_builtin(tmp);
		exit(EXIT_SUCCESS);
	}
	else
		close(tmp->p_fd[1]);
}

void	execution(t_list_exec *list)
{
	t_list_exec	*tmp;
	char		**path;

	list = start_list(list);
	tmp = list;
	path = NULL;
	if (list)
	{
		path = env_path(path, tmp->tools);
		list = here_doc(list);
	}
	while (tmp)
	{
		exec_loop(list, tmp, path);
		if (ft_listsize(list) == 1 && last_token(tmp->sublist) != NO_BUILTIN)
			cmd_one_builtin(list);
		tmp = tmp->next;
	}
	close_wait(list);
	if (path)
		free_env(path);
	free_list_exec(list);
}
