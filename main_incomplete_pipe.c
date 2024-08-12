/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_incomplete_pipe.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 13:31:52 by ehedeman          #+#    #+#             */
/*   Updated: 2024/08/12 09:36:44 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_incomplete_pipe(t_statement *temp)
{
	while (temp)
	{
		if (temp->id && temp->previous->operator == PIPE && !*temp->argv \
				&& !temp->next)
			return (1);
		temp = temp->next;
	}
	return (0);
}

static int	open_pipe_check(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '|')
		{
			if (input_check(input))//invalid input
				return (-1);
			else
			{
				while (input[i] && is_spaces(input[i]))
					i++;
				if (!input[i])
					return (1); //its an open pipe
				if (input[i] == '|')
					return (1); //after the pipe is nothing
			}
		}
		i++;
	}
	return (0); //not an open pipe
}

static int	whitespaces(char *input)
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
	input = NULL;
	return (1);
}

int	complete_pipe(t_statement *temp)
{
	char	*complete;
	t_statement *save;

	save = temp;
	while (temp)
	{
		if (temp->operator == PIPE && !*temp->next->argv)
			break ;
		temp = temp->next;
	}
	free(temp->next->argv);
	free(temp->next);
	temp->next = NULL;
	while (1)
	{
		complete = readline("> ");
		if (!complete)
			return (1);
		if (whitespaces(complete))
			continue ;
		else if (open_pipe_check(complete) == 1)
		{
			temp->next = parsing(complete);
			temp = temp->next;
			free(complete);
		}
		else if (open_pipe_check(complete) == -1)
			return (1);
		else
		{
			if (temp->next)
			{
				free(temp->next->argv);
				free(temp->next);
			}
			temp->next = parsing(complete);
			free(complete);
			break ;
		}
	}
	return (0);
}
