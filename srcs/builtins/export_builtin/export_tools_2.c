/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_tools_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncardozo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 17:34:47 by ncardozo          #+#    #+#             */
/*   Updated: 2023/12/12 23:49:44 by ncardozo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	exp_list_size(t_var_list *list)
{
	int			len;
	t_var_list	*tmp;

	tmp = list;
	len = 0;
	while (tmp)
	{
		tmp = tmp->next;
		++len;
	}
	return (len);
}

void	free_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		free(env[i++]);
	free(env);
}

int	cmp_variable(char *arg1, char *arg2)
{
	char	*tmp1;
	char	*tmp2;
	int		len;
	int		i;

	i = 0;
	tmp1 = NULL;
	tmp2 = NULL;
	len = 0;
	while (arg1[i] && arg1[i++] != '=')
		len++;
	tmp1 = ft_substr(arg1, 0, len);
	i = 0;
	len = 0;
	while (arg2[i] && arg2[i++] != '=')
		len++;
	tmp2 = ft_substr(arg2, 0, len);
	if (ft_strncmp(tmp1, tmp2, ft_strlen(tmp2) + 1) < 0)
	{
		(free(tmp1), free(tmp2));
		return (TRUE);
	}
	(free(tmp1), free(tmp2));
	return (FALSE);
}
