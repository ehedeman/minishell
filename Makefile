# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/19 13:51:06 by ehedeman          #+#    #+#              #
#    Updated: 2024/07/31 16:40:05 by ehedeman         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell
SRC = 	main.c								\
		main_utils.c						\
		main_builtin_commands.c				\
		input_check.c						\
		input_check_two.c					\
		parsing.c							\
		parsing_utils.c						\
		parsing_remove_quotes.c				\
		parsing_remove_quotes_utils.c		\
		p_list_utils.c						\
		cd.c								\
		exit.c								\
		pwd.c								\
		echo.c								\
		history.c							\
		redirect_out.c						\
		redirect_in.c						\
		redirect_in_until_utils.c			\
		redirect_in_utils.c					\
		redirect_special_case.c				\
		redirect_std.c						\
		execute_file.c						\
		execute_file_utils.c				\
		env.c								\
		env_list_utils.c					\
		env_list_print.c					\
		export.c							\
		export_utils.c						\
		unset.c								\
		arg_expansion.c						\
		arg_expansion_utils.c				\
		arg_expansion_utils2.c				\
		arg_expansion_utils3.c				\
		pipes.c								\
		
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
		 --track-fds=yes	\
         --track-origins=yes ./$(NAME)

norm:
	@printf "$(GREEN)"
	@norminette $(SRC) minishell.h
	@printf "$(NC)"

.PHONY: all clean re fclean leaks norm
