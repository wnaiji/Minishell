/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walidnaiji <walidnaiji@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 14:29:54 by wnaiji            #+#    #+#             */
/*   Updated: 2023/11/09 16:38:35 by walidnaiji       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "../lexer/lexer.h"

# define ISSPACE 32
# define EXPAND 36

//////////EXPANDER//////////
//expander.c
t_lexer	expander_by_lexer(t_lexer *lexer);
char	*expander(char *str);

#endif
