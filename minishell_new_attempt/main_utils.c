/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 12:52:43 by ehedeman          #+#    #+#             */
/*   Updated: 2024/08/08 11:50:48 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main_error(int errnum)
{
	if (errnum < 0)
		printf("minishell: %s\n", strerror(errnum));
	if (errnum == MALLOC_ERR)
		write(2, FAILED_MALLOC, ft_strlen(FAILED_MALLOC));
	if (errnum == SYNTAX_ERR)
		write(2, UNEXPECTED_TOKEN, ft_strlen(UNEXPECTED_TOKEN));
	if (errnum == PATH_ERR)
		write(2, FAILED_PATH, ft_strlen(FAILED_PATH));
	if (errnum == FORK_ERR)
		write(2, FAILED_FORK, ft_strlen(FAILED_FORK));
	if (errnum == EXECVE_ERR)
		write(2, FAILED_EXECVE, ft_strlen(FAILED_EXECVE));
	return (-1);
}

int	whitespace_check(t_mini *mini)
{
	int	i;

	i = 0;
	while (mini->input[i])
	{
		if (!is_spaces(mini->input[i]))
			return (0);
		i++;
	}
	free(mini->input);
	mini->input = NULL;
	return (1);
}

void	initialize_mini(t_mini *mini, char **envp)
{
	ft_copy_env2lst(mini, envp);
	init_history(&(mini->history));
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
	mini->com_tab = NULL;
	mini->input = NULL;
	g_sig = 0;
	mini->exit_status = 0;
	mini->fd_out = -1;
	mini->fd_in = -1;
	mini->temp_output = 0;
	mini->additional_args = NULL;
	mini->pwd_save = malloc(PATH_MAX + 1);
	getcwd(mini->pwd_save, PATH_MAX + 1);
	mini->out_path = ft_strjoin(mini->pwd_save, "/.output");
	ft_shlvl(mini);
}

void	handler(int sig)
{
	if (sig == SIGINT && !g_sig)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("\0", 1);
		rl_redisplay();
	}
	if (sig == SIGINT && g_sig == 2)
	{
		g_sig = 3;
		printf("\n");
		rl_replace_line("\0", 1);
	}
	else if (sig == SIGINT && g_sig == 1)
		printf("\n");
	// else if (sig == SIGQUIT && !g_sig)
	// {
	// 	rl_replace_line("\0", 1);
	// 	printf("\n");
	// }
	else if (sig == SIGQUIT && g_sig)
		write(2, "Quit (core dumped)\n", 19);
}

int	ft_shlvl(t_mini *mini)
{
	t_env_list	*current;
	int			num;

	current = mini->env;
	while (current)
	{
		if (current == NULL)
			return (1);
		if (ft_strncmp(current->name, "SHLVL", 5) == 0)
		{
			num = ft_atoi(current->value);
			free(current->value);
			num++;
			current->value = ft_itoa(num);
			break ;
		}
		current = current->next;
	}
	return (0);
}

//to check the input/if everything was parsed correctly
// void	ft_print(t_mini *mini)
// {
// 	int i;
// 	t_statement *temp;
// 	int fd;
// 	char	*nbr;

// 	temp = mini->com_tab;
// 	fd = 1;
// 	printf("fd = %d", fd);
// 	while (temp)
// 	{
// 		i = 0;
// 		nbr = ft_itoa(temp->operator);
// 		write(1, nbr, ft_strlen(nbr));
// 		write(1, "\n", 1);
// 		while (temp->argv[i])
// 		{
// 			write(1, temp->argv[i], ft_strlen(temp->argv[i]));
// 			write(1, "\n", 1);
// 			// printf("%i\n", temp->operator);
// 			// printf("%i\n", temp->argc);
// 			i++;
// 		}
// 		if (temp->previous)
// 				printf("Previous: %s\n", temp->previous->argv[0]);
// 		temp = temp->next;
// 		free(nbr);
// 	}
// }