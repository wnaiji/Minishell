/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walidnaiji <walidnaiji@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 10:56:57 by wnaiji            #+#    #+#             */
/*   Updated: 2023/10/31 20:03:40 by walidnaiji       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*Revoir les fonction une à une sur plusieur possibilité de prompt
	j'en suis au niveau de la fonction is_infile une erreur au niveau de la ligne
	54. Utilisé les modifications apporté dans le is infile au is outfile*/

t_parser	*is_infile(t_lexer **lexer, t_parser *parser)
{
	int		nbr_file;
	int		i;
	char	*tmp;

	if (!*lexer)
		return (parser);
	nbr_file = nbr_infile(*lexer);
	if (nbr_file)
	{
		parser->infile = malloc(sizeof(char *) * (nbr_file + 1));
		if (!(parser->infile))
		return (NULL);
	}
	else
		return (parser);
	i = 0;
	tmp = NULL;
	while (*lexer && (*lexer)->operator != PIPE)
	{
		if ((*lexer)->operator == INFILE || (*lexer)->operator == HEREDOC)
		{
			*lexer = delete_node(*lexer);
			parser->infile[i] = ft_strdup((*lexer)->str);
			*lexer = delete_node(*lexer);
			while (*lexer && (*lexer)->operator == NO_OPERATOR)
			{
				tmp = ft_strjoin(parser->infile[i], (*lexer)->str);
				free(parser->infile[i]);
				parser->infile[i] = ft_strdup(tmp);
				free(tmp);
				lexer = delete_node(*lexer);
			}
			i++;
		}
		else
			*lexer = (*lexer)->next;
	}
	parser->infile[i] = NULL;
	return (parser);
}

t_parser	*is_outfile(t_lexer **lexer, t_parser *parser)
{
	int		nbr_file;
	int		i;
	char	*tmp;

	if (!*lexer)
		return (parser);
	nbr_file = nbr_outfile(*lexer);
	if (nbr_file)
	{
		parser->outfile = malloc(sizeof(char *) * (nbr_file + 1));
		if (!(parser->outfile))
		return (NULL);
	}
	else
		return (parser);
	i = 0;
	tmp = NULL;
	while (*lexer && (*lexer)->operator != PIPE)
	{
		if ((*lexer)->operator == OUTFILE
			|| (*lexer)->operator == OUTFILE_AP_MOD)
		{
			*lexer = delete_node(*lexer);
			parser->outfile[i] = ft_strdup((*lexer)->str);
			while (*lexer && (*lexer)->operator == NO_OPERATOR)
			{
				tmp = ft_strjoin(parser->outfile[i], (*lexer)->str);
				free(parser->outfile[i]);
				parser->outfile[i] = ft_strdup(tmp);
				free(tmp);
				lexer = delete_node(*lexer);
			}
			i++;
		}
		else
			*lexer = (*lexer)->next;
	}
	parser->outfile[i] = NULL;
	return (parser);
}

t_parser	*is_cmd(t_lexer **lexer, t_parser *parser,
				unsigned int nb_arg, int index)
{
	if (!*lexer)
		return (parser);
	while (*lexer && (*lexer)->operator != PIPE)
	{
		nb_arg = 1;
		if ((*lexer)->operator == NO_OPERATOR)
		{
			index = 0;
			nb_arg = nbr_arg_cmd(nb_arg, *lexer);
			while (*lexer && (*lexer)->operator == NO_OPERATOR)
			{
				init_node_cmd(&parser, &*lexer, nb_arg, index++);
				if (*lexer && (*lexer)->operator == SPACE
					&& (*lexer)->next->operator == NO_OPERATOR)
				{
					*lexer = (*lexer)->next;
					init_node_cmd(&parser, &*lexer, nb_arg, index++);
					if (*lexer && (*lexer)->operator == SPACE)
						*lexer = delete_node(*lexer);
				}
			}
		}
		else
			*lexer = (*lexer)->next;
	}
	return (parser);
}

/*t_parser	*is_builtin(t_parser *parser)
{
	t_parser	*first_node;

	while (parser->prev)
		parser = parser->prev;
	first_node = parser;
	while (parser)
	{
		if (parser->operator == CMD)
			parser = init_node_builtin(parser);
		parser = parser->next;
	}
	parser = first_node;
	return (parser);
}*/

void	init_parser(t_lexer *lexer)
{
	unsigned int	nb_arg;
	int				index;
	t_parser		*parser;

	parser = NULL;
	nb_arg = 1;
	index = 0;
	while (lexer)
	{
		parser = parser_add_back_list(parser, NULL);
		while (parser && parser->next)
			parser = parser->next;
		parser = is_infile(&lexer, parser);
		if (lexer && lexer->prev)
			while (lexer->prev)
				lexer = lexer->prev;
		parser = is_outfile(&lexer, parser);
		if (lexer && lexer->prev)
			while (lexer->prev)
				lexer = lexer->prev;
		parser = is_cmd(&lexer, parser, nb_arg, index);
		//builtin
		//lexer = lexer->next; le lexer est supprimé
		//au fur est à mesure nous avons donc pas besoin d passer au suivant
		print_lexer(lexer);
		print_parser(parser);
	}
}
