/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_operators.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 10:38:24 by ehedeman          #+#    #+#             */
/*   Updated: 2024/08/02 15:30:19 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirection_out(t_statement *current, t_mini *mini)
{
	if (current->id == 0 || (current->previous && (current->previous->operator != 3
		&& current->previous->operator != 4)))
	{
		set_temp_output_as_stdout(mini, 0); //reset stdout to output file
		find_command(current, mini);
		reset_stdout(mini);
	}
	find_and_set_last_redirect_out(current, mini); //do all output redirections
	print_output_file(mini);
	reset_stdout(mini);
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
	set_temp_output_as_stdin(mini); //output file is the output for everything so its input for pipes
	do_all_connected_pipes(current, mini); // do all pipes
	reset_stdin(mini);
	return (0);
}
		
int	none(t_statement *current, t_mini *mini)
{
	set_temp_output_as_stdout(mini, 0);
	find_command(current, mini);
	reset_stdout(mini);
	return (0);
}