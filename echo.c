/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:28:15 by ehedeman          #+#    #+#             */
/*   Updated: 2024/08/11 15:53:43 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	remove_quotes_echo(t_statement *temp, int i)
{
	char	*temp_pointer;
	char	buff[4000];

	temp_pointer = temp->argv[i];
	temp->argv[i] = malloc(sizeof(char) * ft_strlen(temp->argv[i]) - 1);
	if (!temp->argv[i])
	{
		ft_printf("minishell: System Error.\n");
		temp->argv[i] = temp_pointer;
		return (-1);
	}
	ft_strlcpy(buff, &temp_pointer[1], ft_strlen(temp->argv[i]));
	ft_strlcpy(temp->argv[i], buff, ft_strlen(temp->argv[i]));
	free(temp_pointer);
	return (0);
}

static bool	check_newline_flag(char **argv, int *i)
{
	if (argv[*i] && !ft_strncmp(argv[*i], "-n", 2) && !argv[*i][2])
	{
		(*i)++;
		return (true);
	}
	return (false);
}

static void	handle_special_cases(t_mini *mini, t_statement *temp, int i)
{
	if (!ft_strcmp(temp->argv[i], "$?"))
		ft_printf("%i\n", mini->exit_status);
	else if (!ft_strncmp(temp->argv[i], "\'$", 2))
	{
		remove_quotes_echo(temp, i);
		ft_printf("%s", temp->argv[i]);
	}
	else
		ft_printf("%s", temp->argv[i]);
}

static int	ft_echo(t_mini *mini, t_statement *temp, int i)
{
	bool	newline;

	i++;
	newline = check_newline_flag(temp->argv, &i);
	while (temp->argv[i])
	{
		handle_special_cases(mini, temp, i);
		if (i < temp->argc - 1 && *temp->argv[i])
			ft_printf(" ");
		i++;
	}
	if (!newline)
		ft_printf("\n");
	return (0);
}

int	check_echo(t_statement *temp, t_mini *mini, int i)
{
	if (!ft_strncmp(temp->argv[i], "echo", ft_strlen("echo") + 1))
	{
		mini->exit_status = ft_echo(mini, temp, i);
		return (1);
	}
	return (0);
}
