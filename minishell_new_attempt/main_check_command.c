/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_check_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 16:47:10 by ehedeman          #+#    #+#             */
/*   Updated: 2024/08/06 16:21:28 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_statement	*check_redirection(t_mini *mini, t_statement *current)
{
	if (current->operator == 1 || current->operator == 2)
	{
		redirection_out(current, mini);
		current = mini->current; //set current to last rdr of output
	}
	if (current->operator == 3)
	{
		if (redirection_in(current, mini))
			return (NULL);
		current = mini->current;
		if (!current)
			return (current);
	}
	if (current->operator == 4)
	{
		redirection_in_until(current, mini);
		current = mini->current;
		if (!current)
			return (current);
	}
	return (current);
}

static t_statement	*check_operators(t_mini *mini, t_statement *current)
{
	current = check_redirection(mini, current);
	if (!current)
		return (NULL);
	if (current->operator == 5)
	{
		pipes(current, mini);
		current = mini->current;
		if (!current)
			return (NULL);
	}
	if (current->operator == NONE)
	{
		none(current, mini);
		current = current->next;
	}
	return (current);
}

static void	check_commands(t_mini *mini, t_statement *first)
{
	t_statement	*current;

	current = first;
	if (!current)
		return ;
	mini->invisible_file = 0;
	if (check_incomplete_pipe(first)) //if theres a incomplete PIPE then complete pipe before anything else
		complete_pipe(first);
	while (current)
	{
		current = check_operators(mini, current);
		if (mini->invisible_file == 1)
			rm_invisible_file(mini, NULL); //from rdr_input_until
		if (!current)
		{
			reset_stdout(mini);
			print_output_file(mini);
			break ;
		}
	}
}

int	execution(t_mini *mini)
{
	mini->current = mini->com_tab;
	mini->fd_out = -1;
	mini->fd_in = -1;
	mini->temp_output = 0;
	if (check_command_after_file_rdr(mini->current)) //is for inverted inpout (> hello echo hello)
		command_after_file_rdr(mini->current, mini);
	if (!mini->current)
	{
		print_output_file(mini);
		return (0);
	}
	check_commands(mini, mini->current);
	return (0);
}
