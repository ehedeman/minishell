/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_check_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 16:47:10 by ehedeman          #+#    #+#             */
/*   Updated: 2024/08/02 13:42:09 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_statement	*check_operators(t_mini *mini, t_statement *current)
{
	if (current->operator == 1 || current->operator == 2)
	{
		redirection_out(current, mini);
		current = mini->current; //set current to last rdr of output
	}
	if (current->operator == 4)
	{
		redirection_in_until(current, mini);
		current = mini->current;
		if (!current)
			return (NULL);
	}
	if (current->operator == 3)
	{
		redirection_in(current, mini);
		current = mini->current;
	}
	if (current->operator == 5)
	{
		pipes(current, mini);
		current = mini->current;
	}
	if (current->operator == NONE)
	{
		none(current, mini);
		current = current->next;
	}
	return (current);
}

static void check_commands(t_mini *mini, t_statement *first)
{
	t_statement *current;

	current = first;
	mini->invisible_file = 0;
	if (check_incomplete_pipe(first)) //if theres a incomplete PIPE then complete pipe before anything else
		complete_pipe(first);
	if (command_involves_pipes(first))
		establish_all_pipes(first);
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
	close_all_pipes(first); // also just in case
}

int	execution(t_mini *mini)
{
	mini->current = mini->com_tab;
	mini->fd_out = -1;
	mini->fd_in = -1;
	mini->temp_output = 0;
	if (check_command_after_file_rdr(mini->current))//is for inverted inpout (> hello echo hello)
		mini->current = command_after_file_rdr(mini->current, mini);
	check_commands(mini, mini->current);
	// printf("\n\nLIST BEFORE RETURNING FROM CHECK_COM:\n");
	// ft_print_env_lst(mini->env);
	return (0);
}
