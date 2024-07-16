/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 10:57:07 by ehedeman          #+#    #+#             */
/*   Updated: 2024/07/16 17:25:57 by ehedeman         ###   ########.fr       */
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
#include <signal.h>

#define OPERATORS "<>|"
#define QUOTES "\"\'"
#define DELIMS "\"\' "
#define REDIRECTS "<>"

#define UNCLOSED_QUOTES "minishell: syntax error unclosed quotes.\n"
#define SYNTAX_ERR_STR "minishell: syntax error.\n"
#define MISSMATCHED_QUOTES "minishell: syntax error missmatched quotes.\n"
#define UNEXPECTED_TOKEN "minishell: syntax error near unexpected token '.\n"
#define UNFINISHED_OUT_RED "minishell: syntax error near unexpected token '>'.\n"
#define UNFINISHED_IN_RED "minishell: syntax error near unexpected token '<'.\n"
#define UNFINISHED_PIPE "minishell: syntax error near unexpected token '|'.\n"
#define FAILED_MALLOC "minishell: failed to allocate needed memory.\n"
#define FAILED_PATH "minishell: failed to find path.\n"
#define FAILED_FORK "minishell: system error regarding forks\n"
#define FAILED_EXECVE "minishell: system error regarding execve\n"

extern int g_exec_file;

typedef enum e_operator {
	NONE = 0,
	RDR_OUT_REPLACE = 1,
	RDR_OUT_APPEND = 2,
	RDR_INPUT = 3,
	RDR_INPUT_UNTIL = 4,
	PIPE = 5,
//	SKIP = 6,
}			t_operator;

typedef enum e_errors {
	MALLOC_ERR = 0,
	SYNTAX_ERR = 2,
	PATH_ERR = 3,
	FORK_ERR = 4,
	EXECVE_ERR = 5,
}			t_errors;

typedef struct	s_statement
{
	int		argc;
	char	**argv;
	t_operator	operator;
	struct s_statement *next;
}				t_statement;

//linked list for env
typedef struct s_env_list
{
	char				*name;
	char				*value;
	struct s_env_list	*next;
}	t_env_list;

typedef struct	s_mini
{
	char	*input;
	int 	operator;
	char	*pwd_save;
	t_statement	*com_tab;
	t_statement *temp;
	t_env_list	*env; //linked list of env var names and values
	int	exit_status;
}				t_mini;


t_statement *parsing(char *input, int i, int j);
int			is_onstr(const char *str, int c);
int			is_spaces(char c);
int			get_argc(char **parsed);
char 		*remove_quotes(char	*parsed);
t_operator	get_operator(char *operator);
t_statement	*p_new_node(int argc);
int			parsing_error(int errnum);
int			ft_cd(t_statement *temp, int i);
int			ft_pwd(int fd);
void		ft_exit(t_mini *mini);
void		free_com_tab(t_mini *mini);
bool		input_check(char *input);
bool		input_check_two(char *input, bool valid);
int			whitespace_check(char *input);

void		check_commands_loop(t_statement *temp, t_mini *mini, int fd, int i);
int			check_redirect(t_mini *mini, t_statement *command);
int			check_builtins(t_statement *temp, t_mini *mini, int i, int fd) ;
t_statement	*command_after_file_rdr(t_statement *temp, t_mini *mini);
int			check_command_after_file_rdr(t_statement *temp);
int			check_for_dollar_quoted(t_statement *temp); //checks if its echo '$PATH', if any other command then quotes get removed
int			remove_quotes_main(t_statement *temp, int i);

int			get_fd(t_statement *temp);
void		ft_echo(t_mini *mini, t_statement *temp, int fd, int i);

void		ft_history(void);

void		ft_print(t_mini *mini, t_statement *current);
int			main_error(int errnum);

int			redirect_input(t_statement *command, t_statement *temp, t_mini *mini);

//functions for redirect_input_until()
char		**init_input(void);
void		free_node_input(t_statement *temp, char **input);
t_statement *create_rm_node(void);
int			copy_content(char **input);
int			reset_stdin(int old_fd);
//int			add_argument(t_statement *temp);
int			rdr_in_until(t_statement *command, t_mini *mini, int fd, int fd_cpy);

int			exec_file(t_statement *temp, t_mini *mini);
int			exec_command(t_statement *temp, t_mini *mini);
int			free_env_args(char **envp, char **args, int arg_zero);//frees the envp and args from the functions above
int			exec_com_fork(t_statement *temp, char **envp, char **args, pid_t pid); //split half of exec_command | norm accurate
int			exec_file_fork(t_statement *temp, char **envp, char **args, pid_t pid);//split half of exec_file | norma accurate

int			exec_file(t_statement *temp, t_mini *mini);
int			exec_command(t_statement *temp, t_mini *mini);


//env functions
void		ft_copy_env2lst(t_mini *mini, char **envp);

//env list functions
void		ft_env_lst_addback(t_env_list **lst, t_env_list *new);
t_env_list *ft_env_lst_new(char *key, char *value);

//print env
int			ft_print_env_lst(t_env_list *env);

//export
int			ft_export(t_mini *mini);
void		print_sorted_env_vars(t_env_list *env, char **env_array, int count);
char		**copy_env_vars(t_env_list *env, int count);
int			count_env_vars(t_env_list *env);
void		sort_env_array(char **arr, int n);
t_env_list 	*ft_env_lst_new(char *key, char *value);
int			ft_env_list_len(t_env_list *env);

//print env
int			print_env_lst(t_env_list *env);

//export
int			ft_export(t_mini *mini);
void		print_export_list(t_env_list *sorted_env);
t_env_list	*copy_linked_list(t_env_list *env);
void		sort_linked_list(t_env_list *temp_env);

//unset
int			ft_unset(t_env_list *env, char *target_name);

//changed the free function so it also del the content of the nodes
void		ft_env_lst_clear(t_env_list *lst, void (*del)(void *)); 

//expansion $
//void		replace_env_vars(char **args);
void		replace_env_vars(char **args, t_mini *mini);
