# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: walidnaiji <walidnaiji@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/11 11:42:09 by wnaiji            #+#    #+#              #
#    Updated: 2023/09/15 10:46:44 by walidnaiji       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_PATH =	src/

SRC_MAIN = $(addprefix $(SRC_PATH), main.c)

LEXER_PATH = $(SRC_PATH)lexer/
SRC_LEXER = $(addprefix $(LEXER_PATH),	basic_parsing.c \
										ft_list.c \
										outils_lexer.c \
										print_error.c \
										lexer.c \
										lexer_management_quoted.c)

#PARSER_PATH = $(SRC_PARSER)parser/
#SRC_PARSER = $(addprefix $(PARSER_PATH),	)

SRC =	$(SRC_MAIN) \
		$(SRC_LEXER)

OBJ_DIR = obj
OBJS = $(patsubst $(SRC_PATH)%.c, $(OBJ_DIR)/%.o, $(SRC))
#OBJS = $(addprefix $(OBJ_DIR)/,$(notdir $(SRC:.c=.o)))
#OBJS = ${SRC:.c=.o}

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
