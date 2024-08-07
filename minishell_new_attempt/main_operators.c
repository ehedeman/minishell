/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_operators.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 10:38:24 by ehedeman          #+#    #+#             */
/*   Updated: 2024/08/07 14:46:45 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirection_out(t_statement *current, t_mini *mini)
{
	int	fd;

	if (check_command_after_file_rdr(mini->current)) //is for inverted inpout (> hello echo hello)
	{
		command_after_file_rdr(mini->current, mini);
		return (0);
	}
	fd = find_and_set_last_redirect_out(current, mini); //do all output redirections
	if (current->id == 0 || (current->previous
			&& (current->previous->operator != 3
				&& current->previous->operator != 4)))
	{
		set_temp_output_as_stdout(mini, 0); //reset stdout to output file
		find_command(current, mini);
		reset_stdout(mini);
	}
	redirect_stdout(mini, fd, 0);
	print_output_file(mini);//print to the right file
	reset_stdout(mini); //reset
	set_temp_output_as_stdout(mini, 0); // to clear output file
	reset_stdout(mini); //reset
	return (0);
}

int	redirection_in_until(t_statement *current, t_mini *mini)
{
	find_and_set_last_redirect_in_until(current, mini);
	set_temp_output_as_stdout(mini, 0);
	find_command(current, mini); // do command
	reset_stdin(mini); //reset stdin so the input can be used normally if nessecary
	return (0);
}

int	redirection_in(t_statement *current, t_mini *mini)
{
	if (find_and_set_last_redirect_in(current, mini)) //look for last, if invalid file then break
		return (1);
	set_temp_output_as_stdout(mini, 0);
	find_command(current, mini); // do command
	reset_stdin(mini); //reset stdin so the input can be used normally if nessecary
	return (0);
}

int	pipes(t_statement *current, t_mini *mini)
{
	do_all_connected_pipes(current, mini); // do all pipes //output file as stdin happens in the function
	return (0);
}

int	none(t_statement *current, t_mini *mini)
{
	if (current->id)
		set_temp_output_as_stdout(mini, 0);
	find_command(current, mini);
	reset_stdout(mini);
	return (0);
}
