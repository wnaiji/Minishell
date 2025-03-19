/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncardozo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 22:29:22 by ncardozo          #+#    #+#             */
/*   Updated: 2023/12/13 11:35:01 by ncardozo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "lexer_expand.h"
# include "minishell.h"
# include <limits.h>

/*                  CD                    */
void		cd_builtin(char **arg, char *env[]);
char		**update_env(char **env);
void		cd_error_output(char *path_arg);
/*                 ECHO                   */
int			is_n_option(const char *arg);
void		echo_builtin(char **arg);
/*                 ENV                    */
void		env_builtin(t_tools *tools, char **cmd);
/*                 EXIT                   */
void		exit_builtin(char **arg);
long		ft_strto_l(const char *str, char **endptr);
int			is_str_digit(char *str);
/*                 EXPORT                 */
int			cmp_variable(char *arg1, char *arg2);
void		export_builtin(char **args, t_tools *tools);
void		print_export(t_var_list *list);
void		put_error(char *arg);
t_var_list	*list_export_add_back_list(t_var_list *list, char *str);
void		*delete_node_export(t_var_list *list);
int			exp_list_size(t_var_list *list);
void		free_env(char **env);
/*                  PWD                   */
void		pwd_builtin(char **arg);
/*                  UNSET                 */
void		unset_builtin(char **args, t_tools *tools);

#endif
