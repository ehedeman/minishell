/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 10:57:07 by ehedeman          #+#    #+#             */
/*   Updated: 2024/08/07 15:33:36 by ehedeman         ###   ########.fr       */
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
#define UNFINI_OUT_RED "minishell: syntax error near unexpected token '>'.\n"
#define UNFINI_IN_RED "minishell: syntax error near unexpected token '<'.\n"
#define UNFINI_PIPE "minishell: syntax error near unexpected token '|'.\n"
#define FAILED_MALLOC "minishell: failed to allocate needed memory.\n"
#define FAILED_PATH "minishell: failed to find path.\n"
#define FAILED_FORK "minishell: system error regarding forks\n"
#define FAILED_EXECVE "minishell: system error regarding execve\n"

extern int	g_sig;

//i was desperate, fuck the norm
typedef struct s_exec
{
	char				**envp;
	char				**args;
	struct s_statement	*current;
}				t_exec;

typedef struct s_remove_quotes
{
	int		size;
	int		i;
	int		j;
	bool	quotes;
	char	quote_c;
}				t_remove_quotes;

typedef enum e_operator
{
	NONE = 0,
	RDR_OUT_REPLACE = 1,
	RDR_OUT_APPEND = 2,
	RDR_INPUT = 3,
	RDR_INPUT_UNTIL = 4,
	PIPE = 5,
}			t_operator;

typedef enum e_errors
{
	MALLOC_ERR = 0,
	SYNTAX_ERR = 2,
	PATH_ERR = 3,
	FORK_ERR = 4,
	EXECVE_ERR = 5,
}			t_errors;

typedef struct s_statement
{
	int					id;
	int					argc;
	char				**argv;
	t_operator			operator;
	struct s_statement	*next;
	struct s_statement	*previous;
	int					pipe_fd[2];
}				t_statement;

typedef struct s_history
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

//for arg expansion
typedef struct s_arg_info
{
	char	*new_arg;
	size_t	new_arg_len;
	size_t	new_arg_capacity;
}				t_arg_info;

typedef struct s_mini
{
	char				*input;
	int					operator;
	char				*pwd_save;
	char				*output_path;
	t_statement			*com_tab;
	t_statement			*current;
	t_env_list			*env;
	int					exit_status;
	t_history			history;
	int					temp_output;
	int					fd_in;
	int					fd_out;
	int					stdout_copy;
	int					stdin_copy;
	pid_t				pid;
	int					invisible_file;//so i know if i need to remove temporary file in rm_in_until
	char				**additional_args; //for the wc > file -l || in testing
	}				t_mini;

//main functions that happen before parsing
//input_check.c
bool		input_check(char *input);

//input_check_utils.c
int			check_incomplete_out_red_1(char *input, int *i, int *redirect);
int			check_missmatched_quotes_1(char *input, char *quote_type, int *i, \
	bool *quotes);

//input_check_two.c
bool		input_check_two(char *input, bool valid);

//parsing (in parsing files, mostly named after functions inside)
t_statement	*parsing(char *input);
char		**parsing_input(char *input);
int			get_nbr_parsed_args(char *input, int i, int count);
int			get_token_len(char *input);
int			make_statement_list(t_statement *current, char **parsed, int i);

char		*remove_quotes(char *parsed);
void		unquoted_cpy(char *parsed, char *unquoted_parsed, t_remove_quotes *rem);
int			copy_quotes_dollar_sign(char *unquoted_parsed, char *parsed);
int			check_quotes_dollar_sign(char *parsed_at_i);
int			is_onstr(const char *str, int c);
int			is_spaces(char c);
int			check_doubles(char *input, int i);
t_operator	get_operator(char *operator);
int			get_argc(char **parsed);
void		index_list(t_statement *temp);
int			parsing_error(int errnum);

//p_list_utils.c
t_statement	*p_new_node(int argc);

//main_utils.c
void		ft_print(t_mini *mini); //remove before eval
int			main_error(int errnum);
int			whitespace_check(t_mini *mini);
void		initialize_mini(t_mini *mini, char **envp);
void		handler(int sig);
int			ft_shlvl(t_mini *mini);

//exit.c
int			ft_exit(t_mini *mini, char *arg);
void		free_com_tab(t_mini *mini);

//main_check_command.c
int			execution(t_mini *mini);

//main_check_command_utils.c
int			find_command(t_statement *current, t_mini *mini);
int			check_builtins(t_statement *current, t_mini *mini, int i); //not static cuz needed by command_after_file_rdr

//main_find_and_set_redirections.c
int			find_and_set_last_redirect_out(t_statement *current, t_mini *mini);
int			find_and_set_last_redirect_in(t_statement *current, t_mini *mini);
void		find_and_set_last_redirect_in_until(t_statement *current, \
				t_mini *mini);

//main_incomplete_pipe.c
int			check_incomplete_pipe(t_statement *temp);
int			complete_pipe(t_statement *temp);

//main_operators.c
int			redirection_out(t_statement *current, t_mini *mini);
int			redirection_in_until(t_statement *current, t_mini *mini);
int			redirection_in(t_statement *current, t_mini *mini);
int			pipes(t_statement *current, t_mini *mini);
int			none(t_statement *current, t_mini *mini);

//main_pipes.c
void		do_all_connected_pipes(t_statement *current, t_mini *mini);

// main_set_output_file.c

int			set_temp_output_as_stdout(t_mini *mini, int mode);
int			set_temp_output_as_stdin(t_mini *mini);
int			print_output_file(t_mini *mini);

//main_remove_output_file.c
void		remove_output_file(t_mini *mini);

int			get_fd(t_statement *temp);

//redirect_command_after_file.c
void		command_after_file_rdr(t_statement *temp, t_mini *mini);
int			check_command_after_file_rdr(t_statement *temp);
int			check_shell(char *argv);

//redirect_std.c
int			redirect_stdout(t_mini *mini, int fd, int mode);
int			reset_stdout(t_mini *mini);
int			redirect_stdin(t_mini *mini, int fd, int mode);
int			reset_stdin(t_mini *mini);
void		reset_std(t_mini *mini);

//redirect_in.c
int			redirect_input(t_statement *current);
void		rm_invisible_file(t_mini *mini, char **input);
t_statement	*redirect_input_until(t_statement *current, char *end_word, \
				t_mini *mini);

//redirect_in_until_utils.c
char		**init_input(void);
t_statement	*create_rm_node(void);
int			copy_content(char **input);

//execute_file.c
int			exec_file(t_statement *temp, t_mini *mini, int i); //i is needed for the special case thing
int			exec_command(t_statement *temp, t_mini *mini, int i);

//execute_file_utils.c
int			exec_com_fork(t_exec *exec, t_mini *mini, int i); //split half of exec_command | norm accurate
int			exec_file_fork(t_exec *exec, t_mini *mini, int i);//split half of exec_file | norma accurate
int			ft_find_array_size(char **array, int i);

//fifty_shades_of_free.c
int			free_env_args(char **envp, char **args, int mode); //frees the envp and args from the functions above
void		free_com_tab(t_mini *mini);
void		free_input(char **input);
void		free_node_input(t_statement *temp, char **input);

//BUILTINS
int			check_echo(t_statement *temp, t_mini *mini, int i);
int			check_cd(t_statement *temp, t_mini *mini, int i);
int			check_pwd(t_statement *temp, t_mini *mini, int i);
int			check_exit(t_statement *temp, t_mini *mini, int i);
int			check_env(t_statement *temp, t_mini *mini, int i);
int			check_export(t_statement *temp, t_mini *mini, int i);
int			check_unset(t_statement *temp, t_mini *mini, int i);

//env
void		ft_copy_env2lst(t_mini *mini, char **envp);
void		ft_env_lst_addback(t_env_list **lst, t_env_list *new);
t_env_list	*ft_env_lst_new(char *key, char *value);
int			ft_print_env_lst(t_env_list *env);

//export
t_env_list	*ft_env_lst_new(char *key, char *value);
int			ft_env_list_len(t_env_list *env);
void		ft_env_lst_clear(t_env_list *lst, void (*del)(void *));
void		ft_print_export_list(t_env_list *sorted_env);
t_env_list	*copy_linked_list(t_env_list *env);
void		sort_linked_list(t_env_list *temp_env);
char		**ft_join_env(char *env_var);

//expansion $
void		replace_env_vars(char **args, t_mini *mini);
void		append_var_value(char **new_arg, const char *var_value);
char		*extract_var_name(char	**arg);
char		*get_env_value(const char *var_name, t_mini *mini);
void		*ft_resize_mem(void *ptr, size_t old_size, size_t new_size);
char		*expand_arg(char *arg, t_mini *mini);
char		*find_next_quote_or_end(char *str, const char *delim);
char		*handle_dollar_sign(char *arg, t_mini *mini, char **new_arg);
char		*append_char_to_new_arg(char *new_arg, char arg_char);
char		*handle_exstat(char **arg, t_mini *mini, char *new_arg, \
				int use_braces);
char		*handle_var_exp(char **arg, t_mini *mini, char *new_arg, \
				int use_braces);

//history
int			check_history(t_statement *temp, t_mini *mini, int i);
void		init_history(t_history *history);	
void		ft_history(const t_history *history);
void		add_to_hist_arr(t_history *history, char *command);
void		free_history(t_history *history);

//testing
void		print_statements(t_statement *statements);