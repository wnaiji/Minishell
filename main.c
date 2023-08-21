/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walidnaiji <walidnaiji@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:58:41 by wnaiji            #+#    #+#             */
/*   Updated: 2023/08/21 16:26:33 by walidnaiji       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*basic_parsing(char *input, t_lexer lexer)
{
	int	i;

	i = 0;
	while (input[i++])
	{
		if (input[i] == INFILE)
		{
			
		}
	}
}

char	*prompt(char *input)
{
	input = readline("minishell> ");
	if (!input)
	{
		printf("exit\n");
		exit(EXIT_SUCESS);
	}
	return (input);
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_lexer	*lexer;

	while (argc == 1)
	{
		input = prompt(input);
	}
	else
		printf("Error: do not give an argument to the executable\n");
	return (0);
}
