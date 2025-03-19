/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncardozo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 15:14:03 by ncardozo          #+#    #+#             */
/*   Updated: 2023/12/10 11:47:12 by ncardozo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdarg.h>
# include <sys/types.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stddef.h>
# include <stdio.h>
# include <limits.h>
# include <math.h>

/*             BASIC FONCTIONS            */
int			ft_atoi(const char *str);
void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t count, size_t size);
char		*ft_itoa(int n);
int			ft_isalnum(int c);
int			ft_isdigit(int c);
void		*ft_memset(void *b, int c, size_t len);
void		ft_putchar_fd(char c, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
void		ft_putstr_fd(char *s, int fd);
char		**ft_split(char const *s, char c);
char		ft_strchr(const char *s, char c);
char		*ft_strdup(const char *src);
char		*ft_strndup(const char *s, size_t n);
char		*ft_strjoin(char *s1, char *s2);
char		*ft_strcpy(char *s1, char *s2);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
int			ft_strlen(const char *s);
int			ft_strncmp(char *s1, char *s2, int n);
char		*ft_strtrim(char *s1, char *set);
char		*ft_substr(char const *s, unsigned int start, size_t len);
int			ft_tolower(int c);

#endif