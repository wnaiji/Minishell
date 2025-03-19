NAME		=	minishell

#               	MAIN_SOURCES				#
SRCS		=	\
				srcs/minishell.c \
#               	BUILTINS_SOURCES			#
SRCS		+=	\
				srcs/builtins/cd_builtin.c \
				srcs/builtins/echo_builtin.c \
				srcs/builtins/env_builtin.c \
				srcs/builtins/exit_builtin/exit_builtin.c \
				srcs/builtins/exit_builtin/exit_tools.c \
				srcs/builtins/exit_builtin/exit_tools_2.c \
				srcs/builtins/export_builtin/export_builtin.c \
				srcs/builtins/export_builtin/print_export.c \
				srcs/builtins/export_builtin/export_tools.c \
				srcs/builtins/export_builtin/export_tools_2.c \
				srcs/builtins/pwd_builtin.c \
				srcs/builtins/unset_builtin/unset_builtin.c \
#               		CTRL_D_SOURCES     		#
SRCS		+= 	\
				srcs/ctrl_d/ctrl_d.c \
#               	EXECUTION_SOURCES			#
SRCS		+= 	\
				srcs/execution/execution.c \
				srcs/execution/execution_2.c \
				srcs/execution/here_doc.c \
				srcs/execution/open_file.c \
				srcs/execution/utils_execution.c \
				srcs/execution/utils_execution_2.c \
				srcs/execution/expander_heredoc.c \
				srcs/execution/utils_expander_heredoc.c \
				srcs/execution/free_list.c \
#               	EXPANDER_SOURCES			#
SRCS		+= 	\
				srcs/expander/expander.c \
				srcs/expander/expander_fonctions.c \
				srcs/expander/expand_utils.c \
#               	PARSING_SOURCES				#
SRCS		+= 	\
				srcs/initial_parsing/free_memory_fonctions.c \
				srcs/initial_parsing/handle_spaces.c \
				srcs/initial_parsing/init_structs.c \
				srcs/initial_parsing/parsing.c \
				srcs/initial_parsing/prompt_special_cases.c \
				srcs/initial_parsing/handle_envp_fonctions.c \
				srcs/initial_parsing/basic_parsing.c \
#               	LEXER_SOURCES				#
SRCS		+=	\
				srcs/lexer/tokenization_fonctions.c \
				srcs/lexer/tokenization_fonctions_2.c \
				srcs/lexer/tokenization_utils.c \
#               	PARSER_SOURCES				#
SRCS		+=	\
				srcs/parser/init_list_parser.c \
				srcs/parser/init_token_builtin.c \
				srcs/parser/outils_parser.c \
				srcs/parser/parser_2.c \
				srcs/parser/parser.c \
				srcs/parser/parser_bis.c \
#               	UTILS_SOURCES				#
SRCS		+=	\
				srcs/tools/error_messages.c \
				srcs/tools/exit_fonctions.c \
				srcs/tools/free_allocated_memory.c \
				srcs/tools/handle_tools.c \
				srcs/tools/list_fonctions.c \
				srcs/tools/list_fonctions_2.c \
#          	 	 MINILIBFT_SOURCES	   			#
SRCS		+=	\
				libft/ft_atoi.c \
				libft/ft_bzero.c \
				libft/ft_calloc.c \
				libft/ft_itoa.c \
				libft/ft_isalnum.c \
				libft/ft_isdigit.c \
				libft/ft_memset.c \
				libft/ft_putchar_fd.c \
				libft/ft_putendl_fd.c \
				libft/ft_putnbr_fd.c \
				libft/ft_putstr_fd.c \
				libft/ft_split.c \
				libft/ft_strchr.c \
				libft/ft_strdup.c \
				libft/ft_strndup.c \
				libft/ft_strjoin.c \
				libft/ft_strcpy.c \
				libft/ft_strlcpy.c \
				libft/ft_strlen.c \
				libft/ft_strncmp.c \
				libft/ft_strtrim.c \
				libft/ft_substr.c \
				libft/ft_tolower.c \
#          	  	 SIGNALS_SOURCES	   			 #
SRCS		+=	\
				srcs/signals/signals.c \
				srcs/signals/signals_tools.c \

OBJDIR				:=	obj/

OBJS				=	$(SRCS:%.c=$(OBJDIR)%.o)

INCS				=	../includes/minishell.h

CC					=	cc

READLINE_INCLUDE	:=	/opt/homebrew/opt/readline/include

CPPFLAGS			:=	-I$(READLINE_INCLUDE)

CFLAGS				=	-Wall -Wextra -Werror $(CPPFLAGS) -Ofast

READLINE_PATH		:=	$(shell brew --prefix readline 2>/dev/null)

READ_LINE			:=	-lreadline -lhistory -L $(READLINE_PATH)/lib

RM					=	rm -rf

SPINNER				=	'-\|/'

$(OBJDIR)%.o: %.c
				@mkdir -p $(@D)
				@$(CC) $(CFLAGS) -c $< -o $@
				@printf "$(shell tput setaf 135)\rCompiling \"$(NAME)\"... $(shell tput sgr0)$(shell tput setaf 193)$<%c $(shell tput sgr0)                                                  " "$(SPINNER)"
				@sleep 0.1

all:			${NAME}

${NAME}:		${OBJS}
				@${CC} $(CFLAGS) $(OBJS) $(READ_LINE) -o $(NAME)
				@make -s norminette

norminette:
				@if norminette $(SRCS) $(INCS) > /dev/null; then \
						echo "\n$(shell tput setaf 135)Norminette: $(shell tput sgr0)$(shell tput setaf 219)[OK]$(shell tput sgr0)"; \
				else \
						echo "\n$(shell tput setaf 135)Norminette: $(shell tput sgr0)$(shell tput setaf 198)[KO]$(shell tput sgr0)"; \
				fi

clean:
				@${RM} $(OBJDIR)/*.o

fclean: clean
				@printf "$(shell tput setaf 135)Removing $(shell tput sgr0)$(shell tput setaf 193)\"$(NAME)\"$(shell tput sgr0)$(shell tput setaf 135) and object directory: $(shell tput sgr0)"
				@${RM} ${NAME}
				@${RM} $(OBJDIR)
				@echo "$(shell tput setaf 219)[OK]$(shell tput sgr0)"

re:				fclean all

.PHONY:			all clean fclean re  norminette
