/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncardozo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 18:26:41 by ncardozo          #+#    #+#             */
/*   Updated: 2023/12/11 18:25:14 by ncardozo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# include "minishell.h"

//		BOOLEANS
# define FALSE 0
# define TRUE 1

//		SEPARATORS
# define SEPARATORS "\'\" <>|"

//		QUOTES
# define EVEN_QUOTES 2
# define ODD_QUOTES 1
# define ZERO_QUOTES 0

//		DIVERS MESSAGES
# define SUCCESS 0
# define FAILURE 1
# define ERROR -1

//		CD MESSAGES
# define CD_NOT_SET 1
# define CD_TOO_MANY_ARGS 2

//		EXIT MESSAGES
# define EXIT_SUCCESS 0
# define EXIT_ERROR 1

//		QUOTES DEFINES

# define PIPE '|'
# define SIMPLE_QUOTE '\''
# define DOUBLE_QUOTE '\"'
# define SPACE ' '
# define INPUT_REDIRECT '<'
# define OUTPUT_REDIRECT '>'
# define HEREDOC "<<"
# define APPEND_REDIRECT ">>"
# define DOLLAR_CHAR '$'
# define DOLLAR "$"
# define BACKSLASH 92
# define POINT_VIRGULE 59
# define PIPELINE 124

//		COMMAND ERROR MESSAGES
# define MALLOC_ERROR -1

//		COMMAND ERROR MESSAGES
# define MSG_ERROR_FILE "No such file or directory"
# define MSG_ERROR_DENIED "Permission denied"
# define MSG_ERROR_TODO "TODO"
# define MSG_ERROR_PIPE "Failed to create pipe"
# define MSG_ERROR_PATH "Failed to find PATH environment variable"
# define MSG_COMMAND_NOT_FOUND "command not found"
# define MSG_ERROR_MEMORY "memory allocation failed"

#endif
