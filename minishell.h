/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walidnaiji <walidnaiji@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 15:09:42 by wnaiji            #+#    #+#             */
/*   Updated: 2023/08/21 16:22:24 by walidnaiji       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <readline/readline.h>

typedef enum e_tokens
{
	infile,
	outfile,
	heredoc,
	outfile_append_mode,
	pipe
}			t_tokens;

typedef struct s_lexer
{
	char			*cmd;
	t_tokens		token;
	int				index;
	struct s_lexer *next;
	struct s_lexer *prev;
}				t_lexer;

#define INFILE <
#define OUTFILE >
#define HEREDOC <<
#define OUT_AP_MO >>
#define PIPE |
#define QUOTE '
#define D_QUOTE "

//Management of linked lists:
// ft_list.c
void	*ft_add_front_list(t_list *list, char *line);
void	*ft_add_back_list(t_list *list, char *line);
void	*ft_delete_in_head(t_list *list);
void	*ft_delete_at_back(t_list *list);
char	*ft_last_content(t_list *list);

#endif
