/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatschu <smatschu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 12:52:43 by ehedeman          #+#    #+#             */
/*   Updated: 2024/07/27 16:53:38 by smatschu         ###   ########.fr       */
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

//to check the input/if everything was parsed correctly
void	ft_print(t_mini *mini)
{
	int i;
	t_statement *temp;
	int fd;
	char	*nbr;

	temp = mini->com_tab;
	fd = 1;
	printf("fd = %d", fd);
	while (temp)
	{
		i = 0;
		nbr = ft_itoa(temp->operator);
		write(1, nbr, ft_strlen(nbr));
		write(1, "\n", 1);
		while (temp->argv[i])
		{
			write(1, temp->argv[i], ft_strlen(temp->argv[i]));
			write(1, "\n", 1);
			// printf("%i\n", temp->operator);
			// printf("%i\n", temp->argc);
			i++;
		}
		if (temp->previous)
				printf("Previous: %s\n", temp->previous->argv[0]);
		temp = temp->next;
		free(nbr);
	}
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
