/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walidnaiji <walidnaiji@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 09:49:21 by ncardozo          #+#    #+#             */
/*   Updated: 2023/12/12 22:28:27 by walidnaiji       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	cd_error_output(char *path_arg)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(path_arg, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(strerror(errno), STDERR_FILENO);
	g_sig = 1;
}

static char	*update_env_loop(char *env, char *pwd, char **old_pwd)
{
	if (!ft_strncmp(env, "PWD=", 4))
	{
		*old_pwd = ft_strdup(env);
		free(env);
		env = ft_strjoin("PWD=", pwd);
	}
	else if (!ft_strncmp(env, "OLDPWD=", 7))
	{
		free(env);
		env = ft_strjoin("OLD", *old_pwd);
		free(*old_pwd);
		*old_pwd = NULL;
	}
	return (env);
}

char	**update_env(char **env)
{
	int		i;
	char	pwd[PATH_MAX];
	char	*old_pwd;

	i = 0;
	if (getcwd(pwd, sizeof(pwd)) == NULL)
	{
		perror("getcwd() error");
		g_sig = 1;
		return (NULL);
	}
	old_pwd = NULL;
	while (env[i])
	{
		env[i] = update_env_loop(env[i], pwd, &old_pwd);
		i++;
	}
	if (old_pwd)
		free(old_pwd);
	return (env);
}

static void	cd_error_message(int message)
{
	if (message == CD_NOT_SET)
		ft_putendl_fd("minishell: cd: HOME not set", STDERR_FILENO);
	else if (message == CD_TOO_MANY_ARGS)
		ft_putendl_fd("minishell: cd: too many arguments", STDERR_FILENO);
	g_sig = 1;
}

void	cd_builtin(char **arg, char *env[])
{
	if (arg[1] == NULL && getenv("HOME"))
	{
		if (chdir(getenv("HOME")) != 0)
		{
			perror("chdir() error");
			return ;
		}
	}
	else if (arg[1] == NULL && !getenv("HOME"))
	{
		cd_error_message(CD_NOT_SET);
		return ;
	}
	else if (arg[2] != NULL)
	{
		cd_error_message(CD_TOO_MANY_ARGS);
		return ;
	}
	else if (chdir(arg[1]) < 0)
	{
		cd_error_output(arg[1]);
		return ;
	}
	env = update_env(env);
	g_sig = 0;
}
