# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smatschu <smatschu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/19 13:51:06 by ehedeman          #+#    #+#              #
#    Updated: 2024/07/10 15:57:29 by smatschu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell
SRC = 	main.c			\
		parsing.c		\
		parsing_utils.c	\
		p_list_utils.c	\
		cd.c			\
		exit.c			\
		pwd.c			\
		input_check.c	\
		redirect_out.c	\
		redirect_in.c	\
		echo.c			\
		main_utils.c	\
		execute_file.c	\
		env.c			\
		env_list_utils.c\
		export.c		\
		export_utils.c	\
		unset.c
OBJS = $(SRC:.c=.o)
OBJS_DIR = objs/
OBJS_PREFIXED = $(addprefix $(OBJS_DIR), $(OBJS))

CC = cc 
CFLAGS = -Werror -Wall -Wextra -g -fsanitize=address -fno-omit-frame-pointer

LIBFT = libft.a
LIB_PATH = ./libft/

RED = \033[0;31m
GREEN = \033[0;32m
NC = \033[0m

all: $(LIBFT) $(CLIENT) $(NAME) #norm

$(NAME): $(OBJS_PREFIXED)
	@$(CC) $(CFLAGS) $(OBJS_PREFIXED) -lreadline -Ilibft -L$(LIB_PATH) -lft -o $(NAME)

$(OBJS_DIR)%.o : %.c minishell.h
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@(cd libft && make all)

clean:
	@rm -rf $(OBJS_DIR)
	@(cd libft && make clean)
	@printf "$(RED)Removed object Files\n$(NC)"

fclean: clean
	@(cd libft && make fclean)
	@printf "$(RED)Removed libft.a\n"
	@rm -f $(NAME)
#	@rm -f $(KILL)
	@printf "$(RED)Removed binary\n$(NC)"

re: fclean all

leaks:
	valgrind --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes ./$(NAME)

norm:
	@printf "$(GREEN)"
	@norminette $(SRC) minishell.h
	@printf "$(NC)"

.PHONY: all clean re fclean leaks norm
