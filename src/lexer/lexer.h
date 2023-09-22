/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walidnaiji <walidnaiji@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 14:55:25 by wnaiji            #+#    #+#             */
/*   Updated: 2023/09/22 10:26:28 by walidnaiji       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdio.h>
# include "../../Libft/libft.h"

# define SIMPLE_QUOTE 39
# define DOUBLE_QUOTE 34
# define BACKSLASH 92
# define POINT_VIRGULE 59
# define PIPELINE 124

typedef enum
{
	NO_OPERATOR,
	PIPE,
	HEREDOC,
	SPACE,
	INFILE,
	OUTFILE,
	OUTFILE_AP_MOD,
	CMD
}		t_operator;

typedef enum
{
	NO_QUOTED,
	SIMPLE_QUOTED,
	DOUBLE_QUOTED
}		t_quoted;

typedef struct	s_lexer
{
	char			*str;
	t_operator		operator;
	int				index;
	t_quoted		quoted;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}				t_lexer;

//////////BASIC_PARSING///////////
//basic_parsing.c
int			check_simple_quote(char *str, int *i);
int			check_double_quote(char *str, int *i);
void		basic_parsing(char *input);

//////////LEXER//////////
//outils_lexer.c
int			forward_in_space(char *input, int *i);
t_operator	token_operator(char *str);
char		*chardup(char c);
char		*charjoin(char *str, char c);
int			special_char(char c);
//lexer_management_quoted.c
t_lexer		*simple_quote(t_lexer *lexer, char *input, int *i);
t_lexer		*double_quote(t_lexer *lexer, char *input, int *i);
t_lexer		*no_quote(t_lexer *lexer, char *input, int *i);
//lexer.c
t_lexer		*operator(t_lexer *lexer, char *input, int *i);
t_lexer		*is_cmd(t_lexer *lexer, char *input, int *i);
t_lexer		*space(t_lexer *lexer, char *input, int *i);
t_lexer		*init_lexer(char *input);

//////////PRINT_ERROR//////////
//print_error.c
void		error_syntax(char *str);

//Management of linked lists:
//init_list_lexer.c
void		*lexer_add_back_list(t_lexer *list, char *line);

//////////PRINT_RESULT//////////
//main.c
void		print_lexer(t_lexer *lexer);

#endif
