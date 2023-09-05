/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walidnaiji <walidnaiji@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:58:41 by wnaiji            #+#    #+#             */
/*   Updated: 2023/08/29 15:36:22 by walidnaiji       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// retourne la redirection ou autre
t_tokens	token_for_lexer(char *input, int len)
{
	if (ft_strchr(input, INFILE) != NULL)
		return (I_FILE);
	else if (ft_strchr(input, OUTFILE) != NULL)
		return (O_FILE);
	else if (ft_strchr(input, HEREDOC) != NULL)
		return (H_DOC);
	else if (ft_strchr(input, OUT_AP_MO) != NULL)
		return (A_MODE);
	else if (ft_strchr(input, PIPE) != NULL)
		return (PIPE_);
}

// Initialisation de chaque maillon
t_list	init_lexer(char *input, t_list *lexer, int start, int len)
{
	static int	index;
	char		*cmd;

	index = 1;
	cmd = NULL;
	if (start != len)
		cmd = ft_substr(input, start, len);
	if (!lexer)
	{
		ft_add_front_list(lexer, cmd);
		lexer->tonken = token_for_lexer(input, len);
		lexer->index = index;
	}
	else
	{
		ft_add_back_list(lexer, cmd);
		lexer->tonken = token_for_lexer(input, len);
		lexer->index = index;
	}
	index++;
	if (cmd)
		free(cmd);
}

// Parsing de l'input, création d'un maillon à chaque fois
// que le caractère est autre q'un alphanum
char	*basic_parsing(char *input, t_list *lexer)
{
	int	i;
	int start;

	i = 0;
	start = 0;
	while (input[i++])
	{
		if (!ft_isalnum(input[i]))
		{
			while ((!ft_isalnum(input[i])) && input[i])
				i++;
			init_lexer(input, lexer, start, i);
			start = i + 1;
		}
	}
	init_lexer(input, lexer, start, i);
}

// Utilisation de readline, elle retourne NULL si ctrl D est utilisé
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
	t_list	*lexer;

	while (argc == 1)
	{
		input = prompt(input);
	}
	else
		printf("Error: do not give an argument to the executable\n");
	return (0);
}
