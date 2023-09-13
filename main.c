/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walidnaiji <walidnaiji@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:58:41 by wnaiji            #+#    #+#             */
/*   Updated: 2023/09/13 15:45:15 by walidnaiji       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//----------------------- visualisation du lexer

void	print_lexer(t_lexer *lexer)
{
	t_lexer	*tmp;
	while (lexer->prev)
		lexer = lexer->prev;
	tmp = lexer;
	while (tmp)
	{
		printf("%s\n", tmp->str);
		tmp = tmp->next;
	}
}

//----------------------- lexer

t_lexer	*simple_quote(t_lexer *lexer, char *input, int *i)
{
	(*i)++;
	if (lexer->str)
		lexer = ft_add_back_list(lexer, NULL);
	if (lexer->next)
		lexer = lexer->next;
	while (input[*i] != SIMPLE_QUOTE)
	{
		if (!lexer->str)
			lexer->str = chardup(input[*i]);
		else
			lexer->str = charjoin(lexer->str, input[*i]);
		(*i)++;
	}
	lexer->quoted = SIMPLE_QUOTED;
	return (lexer);
}

t_lexer	*double_quote(t_lexer *lexer, char *input, int *i)
{
	(*i)++;
	if (lexer->str)
		lexer = ft_add_back_list(lexer, NULL);
	if (lexer->next)
		lexer = lexer->next;
	while (input[*i] != DOUBLE_QUOTE)
	{
		if (!lexer->str)
			lexer->str = chardup(input[*i]);
		else
			lexer->str = charjoin(lexer->str, input[*i]);
		(*i)++;
	}
	lexer->quoted = DOUBLE_QUOTED;
	return (lexer);
}

t_lexer	*no_quote(t_lexer *lexer, char *input, int *i)
{
	if (lexer->str)
		lexer = ft_add_back_list(lexer, NULL);
	if (lexer->next)
		lexer = lexer->next;
	while (input[*i])
	{
		if (special_char(input[*i]) != 0)
			break ;
		else
		{
			if (!lexer->str)
				lexer->str = chardup(input[*i]);
			else
				lexer->str = charjoin(lexer->str, input[*i]);
			(*i)++;
		}
	}
	lexer->quoted = NO_QUOTED;
	return (lexer);
}

t_lexer	*operator(t_lexer *lexer, char *input, int *i)
{
	if (lexer->str)
		lexer = ft_add_back_list(lexer, NULL);
	if (lexer->next)
		lexer = lexer->next;
	lexer->str = chardup(input[*i]);
	if ((input[*i] == '<' && input[*i + 1] == '<')
		|| (input[*i] == '>' && input[*i + 1] == '>'))
		lexer->str = charjoin(lexer->str, input[*i]);
	return (lexer);
}

void	init_lexer(char *input)
{
	int		i;
	t_lexer	*lexer;

	i = 0;
	lexer = NULL;
	while (input[i])
	{
		lexer = ft_add_back_list(lexer, NULL);
		if (lexer->next)
			lexer = lexer->next;
		if (input[i] == SIMPLE_QUOTE)
			lexer = simple_quote(lexer, input, &i);
		else if (input[i] == DOUBLE_QUOTE)
			lexer = double_quote(lexer, input, &i);
		else
		{
			lexer = no_quote(lexer, input, &i);
			if (input[i])
			{
				lexer = operator(lexer, input, &i);
				lexer->operator = token_operator(lexer->str, &i);
			}
		}
		i++;
	}
	print_lexer(lexer);
}

//----------------------- prompt

char	*prompt(char *input)
{
	input = readline("minishell > ");
	if (!input)
	{
		printf("exit\n");
		exit(EXIT_SUCCESS);
	}
	if (input[0] != '\0')
		add_history(input);
	return (input);
}

//----------------------- main

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	(void)argv;
	(void)envp;
	while (argc == 1)
	{
		input = prompt(input);
		basic_parsing(input);
		init_lexer(input);
		//penser a free input
	}
	if (argc > 1)
		printf("Error: do not give an argument to the executable\n");
	return (0);
}
