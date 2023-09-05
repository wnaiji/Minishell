/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walidnaiji <walidnaiji@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 15:09:42 by wnaiji            #+#    #+#             */
/*   Updated: 2023/08/29 15:58:53 by walidnaiji       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <stdlib.h>
# include "Libft/libft.h"

typedef enum e_tokens
{
	I_FILE,
	O_FILE,
	H_DOC,
	PIPE_,
	A_MODE
}			t_tokens;

//LEXER
typedef struct s_lexer
{
	char			*cmd;
	t_tokens		token;
	int				index;
	struct s_lexer *next;
	struct s_lexer *prev;
}				t_lexer;

#define INFILE "<"
#define OUTFILE ">"
#define HEREDOC "<<"
#define OUT_AP_MO ">>"
#define PIPE "|"
//#define QUOTE '
//#define D_QUOTE "

//Management of linked lists:
// ft_list.c
void	*ft_add_front_list(t_lexer *list, char *line);
void	*ft_add_back_list(t_lexer *list, char *line);
void	*ft_delete_in_head(t_lexer *list);
void	*ft_delete_at_back(t_lexer *list);
char	*ft_last_content(t_lexer *list);


#endif
