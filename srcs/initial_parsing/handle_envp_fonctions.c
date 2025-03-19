/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_envp_fonctions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walidnaiji <walidnaiji@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:36:36 by ncardozo          #+#    #+#             */
/*   Updated: 2023/12/12 17:41:29 by walidnaiji       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**stock_new_env(t_var_list *envp)
{
	int			envp_size;
	char		**result;
	int			iter;
	t_var_list	*tmp;

	envp_size = exp_list_size(envp);
	tmp = envp;
	result = malloc(sizeof(char *) * (envp_size + 1));
	if (!result)
	{
		ft_putendl_fd(MSG_ERROR_MEMORY, STDOUT_FILENO);
		return (NULL);
		handle_memory_allocation_error();
	}
	iter = 0;
	while (tmp)
	{
		result[iter] = ft_strdup(tmp->name);
		tmp = tmp->next;
		iter++;
	}
	result[iter] = NULL;
	return (result);
}

char	**stock_env_empty(void)
{
	char	**result;
	char	pwd[PATH_MAX];

	if (getcwd(pwd, sizeof(pwd)) == NULL)
	{
		perror("getcwd() error");
		return (NULL);
	}
	result = malloc(sizeof(char *) * 4);
	if (!result)
		return (NULL);
	result[0] = ft_strjoin("PWD=", pwd);
	result[1] = ft_strdup("SHLVL=1");
	result[2] = ft_strdup("_=/usr/bin/env");
	result[3] = NULL;
	return (result);
}

char	*new_shlvl(char *old_shlvl)
{
	char	*tmp;
	int		iter_lvl;
	char	*new_lvl;

	tmp = getenv(old_shlvl);
	iter_lvl = ft_atoi(tmp);
	iter_lvl += 1;
	tmp = ft_itoa(iter_lvl);
	new_lvl = ft_strjoin("SHLVL=", tmp);
	free(tmp);
	return (new_lvl);
}

char	**stock_env(char **envp)
{
	int		envp_size;
	char	**result;
	int		iter_1;

	envp_size = two_d_array_size(envp);
	result = malloc(sizeof(char *) * (envp_size + 1));
	if (!result)
	{
		ft_putendl_fd(MSG_ERROR_MEMORY, STDOUT_FILENO);
		return (NULL);
		handle_memory_allocation_error();
	}
	iter_1 = -1;
	while (envp[++iter_1] != NULL)
	{
		if (!ft_strncmp(envp[iter_1], "SHLVL=", 6))
			result[iter_1] = new_shlvl(envp[iter_1]);
		else
			result[iter_1] = ft_strdup(envp[iter_1]);
	}
	result[envp_size] = NULL;
	if (envp[0] == NULL)
		result = stock_env_empty();
	return (result);
}
