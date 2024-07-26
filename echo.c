/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatschu <smatschu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:28:15 by ehedeman          #+#    #+#             */
/*   Updated: 2024/07/26 15:52:53 by smatschu         ###   ########.fr       */
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

void	print_argument(char *arg)
{
	printf("%s", arg);
}

void	handle_special_cases(t_mini *mini, t_statement *temp, int i)
{
	if (!ft_strcmp(temp->argv[i], "$?"))
		printf("%i\n", mini->exit_status);
	else if (!ft_strncmp(temp->argv[i], "'$", 2))
	{
		remove_quotes_main(temp, i);
		print_argument(temp->argv[i]);
	}
	else
		print_argument(temp->argv[i]);
}

int	ft_echo(t_mini *mini, t_statement *temp, int i)
{
	bool	newline;

	i++;
	newline = check_newline_flag(temp->argv, &i);
	while (temp->argv[i])
	{
		handle_special_cases(mini, temp, i);
		if (i < temp->argc - 1 && *temp->argv[i])
			printf(" ");
		i++;
	}
	if (!newline)
		printf("\n");
	return (0);
}
