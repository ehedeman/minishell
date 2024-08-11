/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_operators.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 10:38:24 by ehedeman          #+#    #+#             */
/*   Updated: 2024/08/09 16:54:39 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirection_out(t_statement *current, t_mini *mini)
{
	int	fd;

	if (check_command_after_file_rdr(mini->current))
	{
		command_after_file_rdr(mini->current, mini);
		return (0);
	}
	fd = find_and_set_last_redirect_out(current, mini);
	if (current->id == 0 || (current->previous
			&& !(current->previous->operator >= 3
				&& current->previous->operator <= 5)))
	{
		set_temp_output_as_stdout(mini, 0);
		find_command(current, mini, 0);
		reset_stdout(mini);
	}
	redirect_stdout(mini, fd, 0);
	print_output_file(mini);
	reset_stdout(mini);
	set_temp_output_as_stdout(mini, 0);
	reset_stdout(mini);
	return (0);
}

int	redirection_in_until(t_statement *current, t_mini *mini)
{
	if (find_and_set_last_redirect_in_until(current, mini))
		return (1);
	set_temp_output_as_stdout(mini, 0);
	find_command(current, mini, 0);
	reset_stdin(mini);
	return (0);
}

int	redirection_in(t_statement *current, t_mini *mini)
{
	if (find_and_set_last_redirect_in(current, mini))
		return (1);
	set_temp_output_as_stdout(mini, 0);
	find_command(current, mini, 0);
	reset_stdin(mini);
	return (0);
}

int	pipes(t_statement *current, t_mini *mini)
{
	if (just_piepes_left(current))
	{
		do_just_pipes(current, mini);
		mini->current = NULL;
		return (0);
	}
	do_all_connected_pipes(current, mini);
	return (0);
}

int	none(t_statement *current, t_mini *mini)
{
	if (current->id)
		set_temp_output_as_stdout(mini, 0);
	find_command(current, mini, 0);
	reset_stdout(mini);
	return (0);
}
