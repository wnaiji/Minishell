# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: walidnaiji <walidnaiji@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/11 11:42:09 by wnaiji            #+#    #+#              #
#    Updated: 2023/07/29 19:14:35 by walidnaiji       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC =

OBJ_DIR = obj
OBJS = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

NAME = minishell

CFLAGS = -Werror -Wextra -Wall
SUCCESS_MSG = "\033[0;32mCompilation successful. $(NAME) created.\033[0m\n"
ERROR_MSG = "\033[0;31mCompilation failed.\033[0m\n"

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	@gcc $(CFLAGS) -I . -c $< -o $@
	@printf "                   \rCompiling: $<"

$(NAME): $(OBJS)
	@gcc $(CFLAGS) $(OBJS) -o $(NAME)
	@printf "\n"
	@printf $(SUCCESS_MSG)

all: $(NAME)

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -rf $(NAME_BONUS)
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
