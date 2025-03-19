/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walidnaiji <walidnaiji@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 15:14:18 by ncardozo          #+#    #+#             */
/*   Updated: 2023/12/12 22:23:50 by walidnaiji       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_sig = 0;

static void	check_if_valid_line(t_tools *tools, char **temp, int *quotes)
{
	if (is_empty_line(*temp))
		minishell_loop(tools->env);
	tools->command_line = ft_strtrim(*temp, " ");
	*quotes = check_if_quoted_string(tools);
	if (*quotes == ODD_QUOTES)
		error_messages(tools);
}

static void	set_list_for_exec(t_list_exec *parse, t_tools *tools)
{
	t_list_exec	*tmp;

	tmp = parse;
	while (tmp)
	{
		tmp->tools = tools;
		tmp = tmp->next;
	}
	execution(parse);
}

static char	*minishell_prompt(char *temp, t_tools *tools)
{
	if (g_sig == 0)
		temp = readline(MINISHELL_PROMPT1);
	else
		temp = readline(MINISHELL_PROMPT2);
	handle_ctrl_d_inter_mode(tools, temp);
	if (!temp)
	{
		printf("\r\033[1;36mcarnashell\033[1;32m$> \033[0mexit\n");
		exit(EXIT_SUCCESS);
	}
	signal_mode_handling(EXECUTION_MODE);
	return (temp);
}

void	minishell_loop(char **envp)
{
	char			*temp;
	t_node			*list;
	t_tools			*tools;
	t_list_exec		*parse;

	tools = NULL;
	temp = NULL;
	tools = initialise_tools(tools);
	tools->env = stock_env(envp);
	signal_mode_handling(INTERACTIVE_MODE);
	temp = minishell_prompt(temp, tools);
	list = NULL;
	check_if_valid_line(tools, &temp, &tools->quotes_count);
	prompt_back_cases(tools);
	if (tools->command_line && *tools->command_line)
		add_history(tools->command_line);
	tokenizer(tools, &list);
	expander(list, tools);
	parse = init_parser(list);
	set_list_for_exec(parse, tools);
	reset_tools(tools);
	return ;
}

int	main(int ac, char **av, char **envp)
{
	(void)av;
	(void)envp;
	handle_wrong_number_of_argc(ac);
	minishell_loop(envp);
	return (0);
}
