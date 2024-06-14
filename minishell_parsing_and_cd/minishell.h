/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 10:57:07 by ehedeman          #+#    #+#             */
/*   Updated: 2024/06/14 13:52:26 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <sys/wait.h>

#define OPERATORS "<>|"
#define QUOTES "\"\'"
#define DELIMS "\"\' "
#define REDIRECTS "<>"

#define UNCLOSED_QUOTES "minishell: syntax error unclosed quotes.\n"
#define MISSMATCHED_QUOTES "minishell: syntax error missmatched quotes.\n"
#define UNEXPECTED_TOKEN "minishell: syntax error near unexpected token '"
#define FAILED_MALLOC "minishell: failed to allocate needed memory.\n"
#define FAILED_PATH "minishell: failed to find path.\n"

typedef enum e_operator {
	NONE = 0,
	RDR_OUT_REPLACE = 1,
	RDR_OUT_APPEND = 2,
	RDR_INPUT = 3,
	RDR_INPUT_UNTIL = 4,
	PIPE = 5,
}			t_operator;

typedef enum e_errors {
	MALLOC_ERR = 0,
	SYNTAX_ERR = 2,
	PATH_ERR = 3,
}			t_errors;


typedef struct	s_statement
{
	int		argc;
	char	**argv;
	t_operator	operator;
	struct s_statement *next;
}				t_statement;

typedef struct	s_mini
{
	char	*input;
	int 	operator;
	char	*pwd_save;
	t_statement	*com_tab;
}				t_mini;

t_statement *parsing(char *input, int i, int j);
int	is_onstr(const char *str, int c);
int	get_argc(char **parsed);
char *remove_quotes(char	*parsed);
t_operator	get_operator(char *operator);
t_statement	*p_new_node(int argc);
int	parsing_error(int errnum);
void	ft_cd(t_statement *temp, int i);
int	ft_pwd(int fd);
void	ft_exit(t_mini *mini);
void	free_com_tab(t_mini *mini);
bool input_check(char *input);
int	set_fd(char *filename, int red_type);
int	main_error(int errnum);
int	is_path(char *path);

int	check_redirect(t_statement *temp);

