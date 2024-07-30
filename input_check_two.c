/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check_two.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:16:40 by ehedeman          #+#    #+#             */
/*   Updated: 2024/07/30 12:00:20 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_double_pipe(char *input, int i)
{
	int pipe;

	pipe = 0;
	while (input[i])
	{
		while (input[i] != '|' && input[i])
			i++;
		while (input[i] == '|' && input[i])
		{
			pipe++;
			i++;
			if (pipe > 2)
				return (1);
		}
		if (!input[i] && pipe < 2)
			return (0);
		else if (!input[i] && pipe >= 2)
			return (1);
		i++;
	}
	return (0);
}

static int	check_incomplete_pipe_start(char *input, int i)
{
	//int pipe;
	int	character;

	//pipe = 0;
	character = 0;
	while (input[i])
	{
		if (!is_onstr("|", input[i]) && !is_spaces(input[i]))
			character++;
		else if (is_onstr("|", input[i]) && !character)
			return (1);
		i++;
	}
	return (0);
}

static int	check_incomplete_in_red(char *input, int i)
{
	int redirect;

	redirect = 0;
	while (input[i])
	{
		while (input[i] != '<' && input[i])
			i++;
		while (input[i] == '<' && input[i])
		{
			redirect++;
			i++;
			if (redirect > 2)
				return (1);
		}
		while (is_spaces(input[i]) && input[i])
			i++;
		if (is_onstr(OPERATORS, input[i]) && redirect)
			return (1);
		else if (!input[i] && redirect)
			return (1);
		else if (!input[i])
			break ;
		else if (redirect && !is_onstr(OPERATORS, input[i]))
			redirect = 0;
		i++;
	}
	return (0);
}


bool input_check_two(char *input, bool valid)
{
	if (check_double_pipe(input, 0))
	{
		write(1, UNFINISHED_PIPE, ft_strlen(UNFINISHED_PIPE));
		valid = false;
	}
	else if (check_incomplete_pipe_start(input, 0))
	{
		write(1, UNFINISHED_PIPE, ft_strlen(UNFINISHED_PIPE));
		valid = false;
	}
	else if (check_incomplete_in_red(input, 0))
	{
		write(1, UNFINISHED_IN_RED, ft_strlen(UNFINISHED_IN_RED));
		valid = false;
	}
	return (valid);
}
