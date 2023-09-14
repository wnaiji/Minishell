/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walidnaiji <walidnaiji@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:58:41 by wnaiji            #+#    #+#             */
/*   Updated: 2023/09/14 10:14:17 by walidnaiji       ###   ########.fr       */
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
		printf("#####LEXER#####\n");
		printf("CONTENT: %s\n", tmp->str);
		printf("OPERATOR: %d\n", tmp->operator);
		printf("QUOTED: %d\n", tmp->quoted);
		tmp = tmp->next;
	}
}

//----------------------- Parser

//Commencer Par trim les maillons qui sont NO_QUOTED
//Puis supprimer les maillons NULL
/*t_lexer	*first_parsing(t_lexer *lexer)
{
	while (ft_strncmp(ft_last_content(lexer), " ", 2) == 0)
		ft_delete_at_back(lexer);
	while (t_lexer->prev)
		t_lexer = t_lexer->prev;
	while (ft_strncmp(lexer->str, " ", 2) == 0)
		ft_delete_in_head(lexer);
	//vérifier les espaces au milieu
}*/

//trim les string NO_QUOTED

/*void	init_parser(t_lexer *lexer)
{

}*/

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
