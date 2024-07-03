/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 12:52:43 by ehedeman          #+#    #+#             */
/*   Updated: 2024/07/03 14:26:13 by ehedeman         ###   ########.fr       */
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

//to check the input/if everything was parsed correctly
void	ft_print(t_mini *mini, t_statement *current)
{
	int i;
	t_statement *temp;
	int fd;
	char	*nbr;

	temp = mini->com_tab;
	fd = get_fd(current);
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