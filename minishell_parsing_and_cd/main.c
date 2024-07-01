/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 10:57:19 by ehedeman          #+#    #+#             */
/*   Updated: 2024/07/01 15:50:56 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main_error(int errnum)
{
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

//to check the input/if everything was parsed correctly
void	ft_print(t_mini *mini, t_statement *current)
{
	int i;
	t_statement *temp;
	int fd;
	char	*nbr;

	temp = mini->com_tab;
	fd = check_redirect(current);
	while (temp)
	{
		i = 0;
		nbr = ft_itoa(temp->operator);
		write(fd, nbr, ft_strlen(nbr));
		write(fd, "\n", 1);
		while (temp->argv[i])
		{
//			printf("%s\n", temp->argv[i]);
			write(fd, temp->argv[i], ft_strlen(temp->argv[i]));
			write(fd, "\n", 1);
			// printf("%i\n", temp->operator);
			// printf("%i\n", temp->argc);
			i++;
		}
		temp = temp->next;
		free(nbr);
	}
}

int	ft_rm(t_statement *temp)
{
	char *args[] = {"/bin/rm", temp->argv[1], temp->argv[2], NULL };
	char *env[] = { NULL };
	int status;

	pid_t pid = fork();
		
	if (pid == -1)
		return (main_error(FORK_ERR));
	else if (pid == 0)
	{
		if (execve("/bin/rm", args, env) == -1)
			return (main_error(EXECVE_ERR));
	}
	else
		waitpid(pid, &status, 0);
	return (0);
}

void	check_command(t_mini *mini)
{
	t_statement *temp;
	int	i;

	temp = mini->com_tab;
	while (temp)
	{
		i = 0;
		while (temp->argv[i])
		{
			if (ft_strncmp(temp->argv[i], "cd", 2) == 0)
			{
				ft_cd(temp, i);
				if (temp->argv[i + 1])
					i++;
			}
			else if (ft_strncmp(temp->argv[i], "pwd", 3) == 0)
				ft_pwd(check_redirect(temp));
			else if (ft_strncmp(temp->argv[i], "exit", 5) == 0)
				ft_exit(mini);
			else if (ft_strncmp(temp->argv[i], "print", 5) == 0)
			{
				ft_print(mini, temp);
				if (temp->operator == NONE)
					return ;
			}
			else if (ft_strncmp(temp->argv[i], "echo", 4) == 0)
			{
				ft_echo(temp, i);
				break ;
			}
			else if (ft_strncmp(temp->argv[i], "rm", 2) == 0)
			{
				ft_rm(temp);
				return ;
			}
			else if (temp->operator != SKIP)
			{
				write(1, "Command not found.\n", 19);
				return ;
			}
			i++;
		}
		temp = temp->next;
	}
}

int	main(void)
{
	t_mini	mini;

	while (1)
	{
		mini.input = readline("minishell: ");
		if (!mini.input)
		{
			write(2, "Error\n", 6);
			return (0);
		}
		if (*mini.input)
		{
			if (input_check(mini.input))
			{
				add_history(mini.input);
				mini.com_tab = parsing(mini.input, 0 , 0);
				if (!mini.com_tab)
					return (0);
				check_command(&mini);
				if (mini.com_tab)
					free_com_tab(&mini);
			}
		}
	}
	return (0);
}
