/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncardozo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 22:19:40 by ncardozo          #+#    #+#             */
/*   Updated: 2023/11/15 11:09:10 by ncardozo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_special_redirect_cases(t_node *actual)
{
	if (actual->before)
	{
		if ((actual->before->type == TOKEN_INPUT_REDIRECT
				|| actual->before->type == TOKEN_OUTPUT_REDIRECT
				|| actual->before->type == TOKEN_REDIRECT_APPEND))
			return (TRUE);
		else if (actual->before->type == TOKEN_SPACE)
		{
			if (actual->before->before)
			{
				if (actual->before->before->type == TOKEN_INPUT_REDIRECT
					|| actual->before->before->type == TOKEN_OUTPUT_REDIRECT
					|| actual->before->before->type == TOKEN_REDIRECT_APPEND)
					return (TRUE);
			}
		}
	}
	return (FALSE);
}

static char	*expand_line(char *str, int tok_before, t_tools *tools)
{
	char	*tmp;
	char	*new_str;

	tmp = NULL;
	new_str = NULL;
	if (tok_before == TOKEN_REDIRECT_HEREDOC)
		return (str);
	else if (tok_before == TOKEN_INPUT_REDIRECT
		|| tok_before == TOKEN_OUTPUT_REDIRECT
		|| tok_before == TOKEN_REDIRECT_APPEND)
	{
		tmp = ft_strdup(str);
		new_str = expander_heredoc(str, tools);
		if (new_str[0] == '\0')
			new_str = ft_strdup(tmp);
		free(tmp);
	}
	else
		new_str = expander_heredoc(str, tools);
	return (new_str);
}

void	expander(t_node *list, t_tools *tools)
{
	t_node	*tmp;
	int		tok_before;

	if (!list)
		return ;
	tmp = list;
	tok_before = TOKEN_NULL;
	while (tmp)
	{
		if (ft_strchr(tmp->data, '$') != 0
			&& tmp->type != TOKEN_BT_SIMPLE_QUOTES)
		{
			if (tmp->before && tmp->before->type != TOKEN_SPACE)
				tok_before = tmp->before->type;
			else if (tmp->before && tmp->before->type == TOKEN_SPACE)
			{
				if (tmp->before->before)
					tok_before = tmp->before->before->type;
			}
			tmp->data = expand_line(tmp->data, tok_before, tools);
		}
		tmp = tmp->next;
	}
}
