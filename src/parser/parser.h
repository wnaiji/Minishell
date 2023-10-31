/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walidnaiji <walidnaiji@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 10:56:39 by wnaiji            #+#    #+#             */
/*   Updated: 2023/10/31 16:21:03 by walidnaiji       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../lexer/lexer.h"

typedef enum e_builtin
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

typedef struct s_parser
{
	char			**infile;
	char			**outfile;
	char			**cmd;
	t_builtin		builtin;
	struct s_parser	*next;
	struct s_parser	*prev;
}				t_parser;

//////////PARSER//////////
//parser.c
t_parser		*is_infile(t_lexer **lexer, t_parser *parser);
t_parser		*is_outfile(t_lexer **lexer, t_parser *parser);
t_parser		*is_cmd(t_lexer **lexer, t_parser *parser,
					unsigned int nb_arg, int index);
void			init_parser(t_lexer *lexer);
//outils_parser.c
t_builtin		token_builtin(char *str);
char			**split_args(char *str);
char			*strtolower(char *str);
//init_node_parser.c
int				nbr_infile(t_lexer *lexer);
int				nbr_outfile(t_lexer *lexer);
void			init_node_cmd(t_parser **parser, t_lexer **lexer,
					unsigned int nb_arg, int i);
unsigned int	nbr_arg_cmd(unsigned int nb_arg, t_lexer *lexer);
t_parser		*init_node_builtin(t_parser *parser);

//Management of linked lists:
//init_list_parser.c
void			*parser_add_back_list(t_parser *list, char **line);
void			*parser_delete_at_back(t_parser *list);

///////////PRINT_RESULT//////////
//main.c
void			print_parser(t_parser *parser);

#endif
