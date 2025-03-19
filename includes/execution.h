/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncardozo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 16:26:39 by wnaiji            #+#    #+#             */
/*   Updated: 2023/12/11 20:14:03 by ncardozo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# define ISSPACE 32
# define EXPAND 36

//execution.c
int			infile(t_list_exec *list);
int			outfile(t_list_exec *list);
void		wild_exec(t_list_exec *list, char **path);
void		cmd_builtin(t_list_exec *list);
void		execution(t_list_exec *list);
//outils_execution.c
char		**env_path(char **path, t_tools *tools);
char		**last_content(t_sublist *sublist);
t_builtin	last_token(t_sublist *sublist);
int			ft_listsize(t_list_exec *lst);
//outils_execution_2.c
char		*ft_path(char **envp);
t_list_exec	*start_list(t_list_exec *list);
//here_doc.c
int			result_here_doc(int hd_fd, char *limiter, t_tools *tools);
t_list_exec	*here_doc(t_list_exec *list);
//open_file.c
int			open_infile(char *str, t_list_exec *list);
int			open_outfile(char *str, t_list_exec *list);
int			open_ap_mod(char *str, t_list_exec *list);
t_list_exec	*open_file(t_list_exec *list);
//free_list.c
void		free_sublist(t_sublist *sublist);
void		free_list_exec(t_list_exec *list);
void		*delete_node_list(t_list_exec *list);
void		*delete_node_sublist(t_sublist *sublist);

//////////EXPANDER//////////
//expander_heredoc.c
char		*get_env(char *str, t_tools *tools);
char		*replace_expand(char *str, char *new_str, int *i, t_tools *tools);
char		*join(char *str, char *new_str, int *i);
char		*expander_heredoc(char *str, t_tools *tools);
//utils_expander_heredoc.c
int			len_expand(char *str, int index);
char		*chardup(char c);
char		*charjoin(char *str, char c);

#endif
