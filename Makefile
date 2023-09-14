# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: walidnaiji <walidnaiji@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/11 11:42:09 by wnaiji            #+#    #+#              #
#    Updated: 2023/09/14 11:21:56 by walidnaiji       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC =	basic_parsing.c \
		ft_list.c \
		outils_lexer.c \
		print_error.c \
		lexer.c \
		main.c

OBJ_DIR = obj
OBJS = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

NAME = minishell

CFLAGS = -Werror -Wextra -Wall -fsanitize=address -g3
SUCCESS_MSG = "\033[0;32mCompilation successful. $(NAME) created.\033[0m\n"
ERROR_MSG = "\033[0;31mCompilation failed.\033[0m\n"
LIBFT_PATH = ./Libft/

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	@gcc $(CFLAGS) -I . -c $< -o $@
	@printf "                   \rCompiling: $<"

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
	@rm -rf $(NAME_BONUS)
	@rm -rf $(NAME)
	@make fclean -C $(LIBFT_PATH)

re: fclean all

.PHONY: all clean fclean re
