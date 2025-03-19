/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncardozo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 10:56:39 by wnaiji            #+#    #+#             */
/*   Updated: 2023/12/13 11:36:22 by ncardozo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

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
}						t_builtin;

typedef enum e_token
{
	INFILE,
	OUTFILE,
	CMD,
	HERE_DOC,
	AP_MOD
}						t_token;

typedef struct s_sublist
{
	char				**str;
	t_token				tok;
	t_builtin			builtin;
	struct s_sublist	*next;
	struct s_sublist	*before;
}						t_sublist;

typedef struct s_list_exec
{
	t_sublist			*sublist;
	int					hd_fd[2];
	int					fd_in;
	int					fd_out;
	int					p_fd[2];
	t_tools				*tools;
	pid_t				pid;
	int					stdout_copy;
	struct s_list_exec	*next;
	struct s_list_exec	*before;
}						t_list_exec;

//////////PARSER//////////
// parser.c
t_sublist				*init_node_infile(t_node **lexer, t_sublist *sublist);
t_sublist				*init_node_outfile(t_node **lexer, t_sublist *sublist);
t_sublist				*init_node_cmd(t_node **lexer, t_sublist *sublist);
t_sublist				*init_sublist(t_node **lexer);
t_list_exec				*init_parser(t_node *lexer);
// parser_2.c
char					*init_str(t_node **lexer);
char					**is_infile(t_node **lexer);
char					**is_outfile(t_node **lexer);
char					**is_cmd(t_node **lexer);
// outils_parser.c
int						nbr_pipe(t_node *lexer);
int						nbr_arg_cmd(t_node *lexer);
t_list_exec				*start_list(t_list_exec *list);
int						last_content_lexer(t_node *lexer);
// init_token_builtin.c
char					*strtolower(char *str);
t_builtin				token_builtin(char *str);
t_list_exec				*init_node_builtin(t_list_exec *parser);

// Management of linked lists:
// init_list_parser.c
t_list_exec				*list_exec_add_back_list(t_list_exec *list,
							t_sublist *sublist);
t_sublist				*sublist_add_back_list(t_sublist *sublist, char **str);
t_node					*lexer_add_back_list(t_node *lexer, char *str);
void					*delete_node_lexer(t_node *lexer);
t_list_exec				*last_content_list(t_list_exec *parser);

#endif
