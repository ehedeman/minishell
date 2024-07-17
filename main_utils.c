/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatschu <smatschu@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 12:52:43 by ehedeman          #+#    #+#             */
/*   Updated: 2024/07/17 09:44:18 by smatschu         ###   ########.fr       */
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
void	ft_print(t_mini *mini, t_statement *current)
{
	int i;
	t_statement *temp;
	int fd;
	char	*nbr;

	temp = mini->com_tab;
	fd = get_fd(current);
	printf("fd = %d", fd);
	while (temp)
	{
		i = 0;
		nbr = ft_itoa(temp->operator);
		write(1, nbr, ft_strlen(nbr));
		write(1, "\n", 1);
		while (temp->argv[i])
		{
//			printf("%s\n", temp->argv[i]);
			write(1, temp->argv[i], ft_strlen(temp->argv[i]));
			write(1, "\n", 1);
			// printf("%i\n", temp->operator);
			// printf("%i\n", temp->argc);
			i++;
		}
		temp = temp->next;
		free(nbr);
	}
}

int	whitespace_check(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (!is_spaces(input[i]))
			return (0);
		i++;
	}
	free(input);
	return (1);
}