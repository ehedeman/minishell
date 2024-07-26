/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatschu <smatschu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:28:15 by ehedeman          #+#    #+#             */
/*   Updated: 2024/07/26 15:37:55 by smatschu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_newline_flag(char **argv, int *i)
{
	if (argv[*i] && !ft_strncmp(argv[*i], "-n", 2) && !argv[*i][2])
	{
		(*i)++;
		return (true);
	}
	return (false);
}

void	print_argument(char *arg, int fd)
{
	write(fd, arg, ft_strlen(arg));
}

void	handle_special_cases(t_mini *mini, t_statement *temp, int fd, int i)
{
	if (!ft_strcmp(temp->argv[i], "$?"))
		ft_putnbr_fd(mini->exit_status, fd);
	else if (!ft_strncmp(temp->argv[i], "'$", 2))
	{
		remove_quotes_main(temp, i);
		print_argument(temp->argv[i], fd);
	}
	else
		print_argument(temp->argv[i], fd);
}

int	ft_echo(t_mini *mini, t_statement *temp, int fd, int i)
{
	bool	newline;

	i++;
	newline = check_newline_flag(temp->argv, &i);
	while (temp->argv[i])
	{
		handle_special_cases(mini, temp, fd, i);
		if (i < temp->argc - 1 && *temp->argv[i])
			write(fd, " ", 1);
		i++;
	}
	if (!newline)
		write(fd, "\n", 1);
	return (0);
}
