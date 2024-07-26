/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 10:57:07 by ehedeman          #+#    #+#             */
/*   Updated: 2024/07/26 17:08:15 by ehedeman         ###   ########.fr       */
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

extern int g_sig;

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

typedef struct	s_history
{
	char	**commands;
	int		size;
	int		capacity;
	int		oldest;
	int		total;
}				t_history;

//linked list for env
typedef struct s_env_list
{
	char				*name;
	char				*value;
	struct s_env_list	*next;
}	t_env_list;

typedef struct	s_mini
{
	char				*input;
	int 				operator;
	char				*pwd_save;
	t_statement			*com_tab;
	t_statement 		*temp;
	t_env_list			*env;
	int					exit_status;
	t_history			history;
	int					fd;
	int					stdout_copy;
	int					stdin_copy;
	pid_t pid;
}				t_mini;

t_statement	*parsing(char *input);

char		*remove_quotes(char *parsed);
int			unquoted_cpy_loop(char *parsed, char *unquoted_parsed,
				bool quotes, char quote_c);
int			copy_quotes_dollar_sign(char *unquoted_parsed, char *parsed);
int			check_quotes_dollar_sign(char *parsed_at_i);

int			is_onstr(const char *str, int c);
int			is_spaces(char c);
int			check_doubles(char *input, int i);
t_operator	get_operator(char *operator);
int			get_argc(char **parsed);

t_statement	*p_new_node(int argc);
int			parsing_error(int errnum);
int			ft_cd(t_statement *temp, int i);
int			ft_pwd(void);
int			ft_exit(t_mini *mini, char *arg);
void		free_com_tab(t_mini *mini);
bool		input_check(char *input);
bool		input_check_two(char *input, bool valid);
int			whitespace_check(char *input);

void		check_commands_loop(t_statement *temp, t_mini *mini, int fd, int i);
int			check_redirect(t_mini *mini, t_statement *command);
int			check_builtins(t_statement *temp, t_mini *mini, int i) ;
t_statement	*command_after_file_rdr(t_statement *temp, t_mini *mini);
int			check_command_after_file_rdr(t_statement *temp);
int			check_for_dollar_quoted(t_statement *temp); //checks if its echo '$PATH', if any other command then quotes get removed
int			remove_quotes_main(t_statement *temp, int i);

int			get_fd(t_statement *temp);
int		ft_echo(t_mini *mini, t_statement *temp, int i);

void		ft_print(t_mini *mini);
int			main_error(int errnum);

int			redirect_input(t_statement *command, t_statement *temp, t_mini *mini);

int	redirect_stdout(t_mini *mini, int fd);
int	reset_stdout(t_mini *mini);

//functions for redirect_input_until()
char		**init_input(void);
void		free_node_input(t_statement *temp, char **input);
t_statement *create_rm_node(void);
int			copy_content(char **input);
int			reset_stdin(int old_fd);
//int			add_argument(t_statement *temp);
int			rdr_in_until(t_statement *command, t_mini *mini, int fd, int fd_cpy);

//execution
int			exec_file(t_statement *temp, t_mini *mini);
int			exec_command(t_statement *temp, t_mini *mini);
int			free_env_args(char **envp, char **args, int arg_zero);//frees the envp and args from the functions above
int			exec_com_fork(t_statement *temp, char **envp, char **args, t_mini *mini); //split half of exec_command | norm accurate
int			exec_file_fork(t_statement *temp, char **envp, char **args, t_mini *mini);//split half of exec_file | norma accurate

//env
void		ft_copy_env2lst(t_mini *mini, char **envp);
void		ft_env_lst_addback(t_env_list **lst, t_env_list *new);
t_env_list *ft_env_lst_new(char *key, char *value);
int			ft_print_env_lst(t_env_list *env);

//export
int			ft_export(t_mini *mini);
t_env_list 	*ft_env_lst_new(char *key, char *value);
int			ft_env_list_len(t_env_list *env);
void		ft_env_lst_clear(t_env_list *lst, void (*del)(void *)); 
void		ft_print_export_list(t_env_list *sorted_env);
t_env_list	*copy_linked_list(t_env_list *env);
void		sort_linked_list(t_env_list *temp_env);

//unset
int			ft_unset(t_env_list *env, char *target_name);


//expansion $
void	replace_env_vars(char **args, t_mini *mini);
void	append_var_value(char **new_arg, const char *var_value);
char	*extract_var_name(char	**arg);
char	*get_env_value(const char *var_name, t_mini *mini);
void	*ft_resize_mem(void *ptr, size_t new_size);
int		start_and_end_with_single_quotes(const char *str, size_t len);


//history
void	init_history(t_history *history);	
void	ft_history(const t_history *history);
void	add_to_hist_arr(t_history *history, char *command);
void	free_history(t_history *history);

//pipes
int		command_involves_pipes(t_statement *parsed_input);
int		create_pipe(int pipefd[]);
void	execute_pipeline(t_statement *commands, t_mini *mini);
