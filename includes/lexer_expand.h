/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_expand.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncardozo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 07:20:09 by ncardozo          #+#    #+#             */
/*   Updated: 2023/12/13 11:35:48 by ncardozo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_EXPAND_H
# define LEXER_EXPAND_H
# include "minishell.h"

typedef enum e_token_type
{
	TOKEN_NULL,
	TOKEN_PIPE,
	TOKEN_INPUT_REDIRECT,
	TOKEN_OUTPUT_REDIRECT,
	TOKEN_REDIRECT_HEREDOC,
	TOKEN_REDIRECT_APPEND,
	TOKEN_WORD,
	TOKEN_BT_SIMPLE_QUOTES,
	TOKEN_BT_DOUBLE_QUOTES,
	TOKEN_SPACE,
	TOKEN_DOLLAR,
}							t_token_type;

typedef struct s_node
{
	char					*data;
	char					*var_name;
	char					*var_value;
	t_token_type			type;
	struct s_node			*next;
	struct s_node			*before;
}							t_node;

typedef struct s_var_list
{
	char				*name;
	struct s_var_list	*before;
	struct s_var_list	*next;
}						t_var_list;

typedef struct s_tools
{
	char					*command_line;
	char					**env;
	const char				*pos;
	const char				*temp_pos;
	char					*result;
	char					*out;
	char					*data;
	char					quote_type;
	char					actual_sep;
	int						iter;
	int						string_len;
	int						quotes_count;
	t_var_list				*envp_list;
}							t_tools;

typedef struct s_prompt_list
{
	struct s_command_list	*command_list;
	struct s_prompt_list	*next;
	struct s_prompt_list	*before;
}							t_prompt_list;

/*                 EXPANDER               */
void						parse_expand(t_node **list);
void						expander(t_node *list, t_tools *tools);
int							count_dollars(const char **pos);
int							dollar_chr(char *data);
int							is_heredoc_redirec(t_node *actual);
int							is_redirect_or_append(t_node *actual);
void						remove_node_if_needed(t_node **list, t_node *node);
void						replace_token_word(t_node *actual_list,
								char *new_data);
t_node						*pop_first_unexistant_var(t_node **actual,
								t_node **list);
t_node						*pop_unexistant_var(t_node **actual);

/*              HANDLE_TOOLS              */
t_tools						*initialise_tools(t_tools *tools);
void						reset_ex_tools(t_tools *ex_tools);
int							reset_tools(t_tools *tools);
char						**stock_new_env(t_var_list *envp);
char						**stock_env_empty(void);
char						*new_shlvl(char *old_shlvl);
char						**stock_env(char **envp);
int							ft_lstsize(t_node *lst);
int							two_d_array_size(char **envp);
/*                   LEXER                */
char						is_a_separator(char to_check);
void						search_type_of_quote(t_tools *tools);
void						tokenize_pipe_char(t_tools *tools, t_node **list);
void						tokenize_redirect_chars(t_tools *tools,
								t_node **list);
void						tokenize_space_char(t_tools *tools, t_node **list);
void						tokenizer(t_tools *tools, t_node **list);

/*              LIST_FONCTIONS            */
t_node						*create_list(void);
t_node						*create_new_node(char *data, t_token_type type);
void						*delete_node(t_node *list);
void						free_list(t_node **list);
int							list_size(t_node *list);
void						pop_back_list(t_node **list);
void						pop_front_node(t_node **list);
void						push_back_list(t_node **list, char *data,
								t_token_type type);
void						put_list(t_node *list);

/*                 PARSING                */
int							check_if_quoted_string(t_tools *tools);
void						free_node_data(t_node *node);
void						free_string_variable(char *str);
void						handle_wrong_number_of_argc(int ac);
int							is_empty_line(char *str);
int							is_space(char c);
char						*remove_spaces(char *str);
int							basic_parsing(char *input);
int							check_double_quote(char *str, int *i);
int							check_simple_quote(char *str, int *i);

#endif
