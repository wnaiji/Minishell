# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: walidnaiji <walidnaiji@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/11 11:42:09 by wnaiji            #+#    #+#              #
#    Updated: 2023/11/09 17:13:32 by walidnaiji       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_PATH =	src/

SRC_MAIN = $(addprefix $(SRC_PATH), main.c)

LEXER_PATH = $(SRC_PATH)lexer/
SRC_LEXER = $(addprefix $(LEXER_PATH),	basic_parsing.c \
										init_list_lexer.c \
										outils_lexer.c \
										print_error.c \
										lexer.c \
										lexer_management_quoted.c)

EXPANDER_PATH = $(SRC_PATH)expander/
SRC_EXPANDER = $(addprefix $(EXPANDER_PATH),	expander.c \
												outils_expander.c)

PARSER_PATH = $(SRC_PATH)parser/
SRC_PARSER = $(addprefix $(PARSER_PATH),	parser.c \
											outils_parser.c \
											init_list_parser.c \
											init_node_parser.c)

SRC =	$(SRC_MAIN) \
		$(SRC_LEXER) \
		$(SRC_PARSER) \
		$(SRC_EXPANDER)

OBJ_DIR = obj
OBJS = $(patsubst $(SRC_PATH)%.c, $(OBJ_DIR)/%.o, $(SRC))

NAME = minishell

CFLAGS = -Werror -Wextra -Wall -fsanitize=address -g3
SUCCESS_MSG = "\033[0;32mCompilation successful. $(NAME) created.\033[0m\n"
ERROR_MSG = "\033[0;31mCompilation failed.\033[0m\n"
LIBFT_PATH = ./Libft/

$(OBJ_DIR)/%.o: $(SRC_PATH)%.c
	@mkdir -p $(@D)
	@gcc $(CFLAGS) -I . -c $< -o $@
	@printf "                                                    \rCompiling: $<"

$(NAME): $(OBJS)
	@make -C $(LIBFT_PATH)
	@gcc $(CFLAGS) $(OBJS) -L $(LIBFT_PATH) -l ft -l readline -o $(NAME)
	@printf "\n"
	@printf $(SUCCESS_MSG)

all: $(NAME)

clean:
	@rm -rf $(OBJ_DIR)
	@make clean -C $(LIBFT_PATH)

fclean: clean
	@rm -rf $(NAME)
	@make fclean -C $(LIBFT_PATH)

re: fclean all

.PHONY: all clean fclean re
