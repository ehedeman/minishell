/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_check_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 16:47:10 by ehedeman          #+#    #+#             */
/*   Updated: 2024/08/01 15:37:47 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_statement	*check_operators(t_mini *mini, t_statement *current)
{
	if (current->operator == 1 || current->operator == 2)
	{
		find_and_set_last_redirect_out(current, mini); //do all output redirections
		find_command(current, mini);
		set_temp_output_as_stdout(mini); //reset stdout to output file
		current = mini->current; //set current to last rdr of output
	}
	if (current->operator == 3)
	{
		find_and_set_last_redirect_in_until(current, mini); //look for last
		find_command(current, mini); // do command
		reset_stdin(mini); //reset stdin so the input can be used normally if nessecary
		current = mini->current;
	}
	if (current->operator == 4)
	{
		if (find_and_set_last_redirect_in(current, mini)) //look for last, if invalid file then break
			return (NULL);
		find_command(current, mini); // do command
		reset_stdin(mini); //reset stdin so the input can be used normally if nessecary
		current = mini->current;
	}
	if (current->operator == 5)
	{
		set_temp_output_as_stdin(mini); //output file is the output for everything so its input for pipes
		do_all_connected_pipes(current, mini); // do all pipes
		current = mini->current;
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
		reset_std(mini); //just in case
		if (mini->invisible_file == 1)
			rm_invisible_file(mini, NULL); //from rdr_input_until
		if (current) //just in case
			current = current->next;
	}
	close_all_pipes(first); // also just in case
}

int	check_command(t_mini *mini)
{
	mini->current = mini->com_tab;
	mini->fd_out = -1;
	mini->fd_in = -1;
	mini->temp_output = 0;
	if (check_command_after_file_rdr(mini->current))
		mini->current = command_after_file_rdr(mini->current, mini);
	set_temp_output_as_stdout(mini);
	check_commands(mini, mini->current);
	// printf("\n\nLIST BEFORE RETURNING FROM CHECK_COM:\n");
	// ft_print_env_lst(mini->env);
	return (0);
}
