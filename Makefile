# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ehedeman <ehedeman@student.42wolfsburg.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/19 13:51:06 by ehedeman          #+#    #+#              #
#    Updated: 2024/08/11 16:22:42 by ehedeman         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell
SRC = 	main.c								\
		main_utils.c						\
		main_check_command.c				\
		main_check_command_utils.c			\
		main_find_and_set_redirections.c	\
		main_incomplete_pipe.c				\
		main_just_pipes_left.c				\
		main_just_pipes_utils.c				\
		main_operators.c					\
		main_print_output_file.c			\
		main_pipes.c						\
		main_set_output_file.c				\
		main_remove_output_file.c			\
		add_arg_to_argv.c					\
		add_arg_to_argv_utils.c				\
		input_check.c						\
		input_check_utils.c					\
		input_check2.c						\
		parsing.c							\
		parsing_get_nbr_parsed_args.c		\
		parsing_get_token_length.c			\
		parsing_input.c						\
		parsing_make_statement_list.c		\
		parsing_utils.c						\
		parsing_remove_quotes.c				\
		parsing_remove_quotes_utils.c		\
		parsing_unquoted_cpy.c				\
		p_list_utils.c						\
		fifty_shades_of_free.c				\
		cd.c								\
		exit.c								\
		pwd.c								\
		echo.c								\
		history.c							\
		redirect_out.c						\
		redirect_in.c						\
		redirect_in_until_utils.c			\
		redirect_check_command_after_file.c	\
		redirect_command_after_file.c		\
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

all: $(NAME) #norm

$(NAME): $(LIBFT) $(OBJS_PREFIXED)
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
