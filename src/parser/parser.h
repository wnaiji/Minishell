/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walidnaiji <walidnaiji@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 10:56:39 by wnaiji            #+#    #+#             */
/*   Updated: 2023/09/23 16:49:02 by walidnaiji       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#include "../lexer/lexer.h"

typedef enum
{
	NO_BUILTIN,
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT
}		t_builtin;

typedef enum
{
	NO_IO,
	STDIN,
	STDOUT,
	IN_PIPE,
	OUT_PIPE
}		t_io;

typedef struct	s_parser
{
	char			*str;
	char			**cmd;
	t_builtin		builtin;
	t_io			io;
	t_operator		operator;
	struct s_parser	*next;
	struct s_parser	*prev;
}				t_parser;

//////////PARSER//////////
//parser.c
t_parser	*is_infile(t_lexer **lexer, t_parser *parser);
t_parser	*is_cmd_or_builtin(t_lexer **lexer, t_parser *parser);
t_parser	*is_outfile(t_lexer **lexer, t_parser *parser);
void		init_parser(t_lexer *lexer);
//outils_parser.c
int			is_builtin(char *str);
char		**split_args(char *str);
char		*strtolower(char *str, int operator);
t_parser	*init_node_parser(t_parser *parser);
//init_node_parser.c
void		init_node_infile(t_parser **parser, t_lexer **lexer, char **tmp);
void		init_node_outfile(t_parser **parser, t_lexer **lexer, char **tmp);

//Management of linked lists:
//init_list_parser.c
void		*parser_add_back_list(t_parser *list, char *line);
//void		*delete_node(t_lexer *list);
void		*parser_delete_at_back(t_parser *list);
char		*parser_last_content(t_parser *list);

///////////PRINT_RESULT//////////
//main.c
void	print_parser(t_parser *parser);

#endif
