/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walidnaiji <walidnaiji@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:58:41 by wnaiji            #+#    #+#             */
/*   Updated: 2023/09/24 10:51:48 by walidnaiji       ###   ########.fr       */
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

//----------------------- visualisation du parser

void	print_parser(t_parser *parser)
{
	if (!parser)
		return ;
	t_parser	*tmp;
	//int			i;

	while (parser->prev)
		parser = parser->prev;
	tmp = parser;
	//i = 0;
	while (tmp)
	{
		printf("#####PARSER#####\n");
		//while (parser->cmd[i])
		//{
		//	printf("CMD:		#%s#\n", parser->cmd[i]);
		//	i++;
		//}
		printf("CONTENT:	#%s#\n", tmp->str);
		printf("BUILTIN:	#%d#\n", tmp->builtin);
		printf("REDIREC:	#%d#\n", tmp->operator);
		tmp = tmp->next;
	}
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
		basic_parsing(input); //faire en sorte lors d'une erreur la fonction renvoie sur un prompt
		init_parser(init_lexer(input)); //faire l'expender entre le lexer et le parser
	}
	if (argc > 1)
		printf("Error: do not give an argument to the executable\n");
	return (0);
}
