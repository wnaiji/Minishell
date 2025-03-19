/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walidnaiji <walidnaiji@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 19:19:42 by wnaiji            #+#    #+#             */
/*   Updated: 2023/12/12 18:45:06 by walidnaiji       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_envp(char **envp, char *str)
{
	int		i;
	char	*tmp;
	char	*env;

	i = 0;
	tmp = ft_strjoin(str, "=");
	env = NULL;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], tmp, ft_strlen(tmp)))
			env = ft_strdup(envp[i]);
		i++;
	}
	if (env)
		env = ft_strtrim(env, tmp);
	free(tmp);
	return (env);
}

char	*get_env(char *str, t_tools *tools)
{
	char	*env;

	if (!str)
		return ("\0");
	if (!ft_strncmp(str, "?", 2))
		env = ft_itoa(g_sig);
	else
		env = ft_envp(tools->env, str);
	if (!env)
		return (ft_strdup("\0"));
	return (env);
}

char	*replace_expand(char *str, char *new_str, int *i, t_tools *tools)
{
	char	*tmp;
	char	*tmp2;
	char	*env;
	int		len;

	tmp = NULL;
	len = len_expand(str, *i + 1);
	env = ft_substr(str, *i + 1, len);
	if (new_str)
	{
		tmp2 = get_env(env, tools);
		tmp = ft_strjoin(new_str, tmp2);
		free(tmp2);
		free(new_str);
	}
	else
	{
		tmp2 = get_env(env, tools);
		tmp = ft_strdup(tmp2);
		free(tmp2);
	}
	free(env);
	*i += len + 1;
	return (tmp);
}

char	*join(char *str, char *new_str, int *i)
{
	char	*tmp;

	tmp = NULL;
	if (new_str)
	{
		tmp = charjoin(new_str, str[*i]);
		free(new_str);
	}
	else
		tmp = chardup(str[*i]);
	*i += 1;
	return (tmp);
}

char	*expander_heredoc(char *str, t_tools *tools)
{
	char	*new_str;
	int		i;

	if (ft_strchr(str, EXPAND) == 0)
		return (str);
	i = 0;
	new_str = NULL;
	while (str[i])
	{
		if (str[i] == EXPAND && str[i + 1] != EXPAND && str[i + 1]
			&& str[i + 1] != ISSPACE)
			new_str = replace_expand(str, new_str, &i, tools);
		else
			new_str = join(str, new_str, &i);
	}
	free(str);
	return (new_str);
}
