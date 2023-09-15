/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walidnaiji <walidnaiji@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:58:41 by wnaiji            #+#    #+#             */
/*   Updated: 2023/09/14 21:26:58 by walidnaiji       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//----------------------- visualisation du lexer

void	print_lexer(t_lexer *lexer)
{
	if (!lexer)
		return ;
	t_lexer	*tmp;
	while (lexer->prev)
		lexer = lexer->prev;
	tmp = lexer;
	while (tmp)
	{
		printf("#####LEXER#####\n");
		printf("CONTENT: #%s#\n", tmp->str);
		printf("OPERATOR: #%d#\n", tmp->operator);
		printf("QUOTED: #%d#\n", tmp->quoted);
		tmp = tmp->next;
	}
}

//----------------------- Parser

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
		basic_parsing(input); //faire en sorte lors d'une erreur la fonction renvoie sur un prompt
		init_lexer(input); // free input à la sortie
		//penser a free input
	}
	if (argc > 1)
		printf("Error: do not give an argument to the executable\n");
	return (0);
}
