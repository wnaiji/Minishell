/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walidnaiji <walidnaiji@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 14:55:25 by wnaiji            #+#    #+#             */
/*   Updated: 2023/09/13 19:47:32 by walidnaiji       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include "Libft/libft.h"

# define SIMPLE_QUOTE 39
# define DOUBLE_QUOTE 34
# define BACKSLASH 92
# define POINT_VIRGULE 59
# define PIPELINE 124

typedef enum
{
	PIPE,
	HEREDOC,
	SPACE,
	INFILE,
	OUTFILE,
	OUTFILE_AP_MOD,
	NO_OPERATOR
}		t_operator;

typedef enum
{
	SIMPLE_QUOTED,
	DOUBLE_QUOTED,
	NO_QUOTED,
}		t_quoted;

typedef enum
{
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT,
	NO_BUILTIN
}

typedef struct	s_lexer
{
	char			*str;
	t_operator		operator;
	int				index;
	t_quoted		quoted;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}				t_lexer;

typedef struct	s_parser
{
	char			**str;
	t_builtin		builtin;
	t_operator		redirection;
	struct s_parser	*next;
	struct s_parser	*prev;
}				t_parser;

//////////BASIC_PARSING///////////
//basic_parsing.c
int	check_simple_quote(char *str, int *i);
int	check_double_quote(char *str, int *i);
void	basic_parsing(char *input);

//////////LEXER//////////
//outils_lexer.c
t_operator	token_operator(char *str, int *i);
char	*chardup(char c);
char	*charjoin(char *str, char c);
int	special_char(char c);
//lexer.c
t_lexer	*simple_quote(t_lexer *lexer, char *input, int *i);
t_lexer	*double_quote(t_lexer *lexer, char *input, int *i);
t_lexer	*no_quote(t_lexer *lexer, char *input, int *i);
t_lexer	*operator(t_lexer *lexer, char *input, int *i);
void	init_lexer(char *input);

//////////PARSER//////////

//////////PRINT_ERROR//////////
//print_error.c
void	error_syntax(char *str);

//Management of linked lists:
// ft_list.c
void	*ft_add_front_list(t_parser *list, char *line);
void	*ft_add_back_list(t_lexer *list, char *line);
void	*ft_delete_in_head(t_lexer *list);
void	*ft_delete_at_back(t_lexer *list);
char	*ft_last_content(t_lexer *list);

#endif
