/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walidnaiji <walidnaiji@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 10:35:15 by wnaiji            #+#    #+#             */
/*   Updated: 2023/09/15 10:59:05 by walidnaiji       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

//Erreur de sortie quand la syntax n'est pas bonne
//elle sera que temporaire
void	error_syntax(char *str)
{
	printf("minishell: syntax error near unexpected token `%s'\n", str);
}
