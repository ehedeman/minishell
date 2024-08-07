/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_command_after_file.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatschu <smatschu@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 15:24:10 by ehedeman          #+#    #+#             */
/*   Updated: 2024/08/07 22:21:07 by smatschu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_commands_rdr(t_statement *current, t_mini *mini, int i)
{
	while (i < current->argc && *current->argv)
	{
		if (check_builtins(current, mini, i))
			break ;
		if (!ft_strncmp(current->argv[i], "./", 2)
			|| !ft_strncmp(current->argv[i], "/", 1))
		{
			reset_std(mini);
			if (exec_file(current, mini, 1) == -1)
				return (-1);
			break ;
		}
		else
		{
			if (check_shell(current->argv[i]))
				reset_std(mini);
			exec_command(current, mini, 1);
			return (0);
		}
		i++;
	}
	return (0);
}

static void	rdr_out(t_statement *current, t_mini *mini)
{
	int	fd;

	while ((current->operator == RDR_OUT_REPLACE
			|| current->operator == RDR_OUT_APPEND) && current)
	{
		fd = get_fd(current);
		if (current->next->operator == RDR_OUT_REPLACE
			|| current->next->operator == RDR_OUT_APPEND)
			close(fd);
		else
		{
			current = current->next;
			break ;
		}
		current = current->next;
	}
	set_temp_output_as_stdout(mini, 0);
	reset_stdout(mini);
	redirect_stdout(mini, fd, 0);
	check_commands_rdr(current, mini, 1);
	reset_stdout(mini);
	if (current->operator == NONE)
		mini->current = current->next;
	else
		mini->current = current;
}

static void	rdr_in_until(t_statement *current, t_mini *mini)
{
	char	*end_word;

	end_word = NULL;
	if (current->next)
		end_word = current->next->argv[0];
	current = redirect_input_until(current, end_word, mini);
	set_temp_output_as_stdout(mini, 0);
	check_commands_rdr(current, mini, 1);
	reset_stdin(mini);
	reset_stdout(mini);
	if (current->operator == NONE)
		mini->current = current->next;
	else
		mini->current = current;
	rm_invisible_file(mini, NULL);
	mini->invisible_file = 0;
}

static t_statement	*rdr_in(t_statement *current, t_mini *mini, int fd)
{
	while (current)
	{
		if (current->operator == 3)
		{
			fd = redirect_input(current);
			if (fd == -1)
				return (NULL);
			if (current->next && current->next->operator == 3)
				close(fd);
		}
		if (current->operator != 3)
			break ;
		current = current->next;
	}
	redirect_stdin(mini, fd, 0);
	set_temp_output_as_stdout(mini, 0);
	check_commands_rdr(current, mini, 1);
	reset_stdin(mini);
	reset_stdout(mini);
	if (current->operator == NONE)
		return (current->next);
	else
		return (current);
}

void	command_after_file_rdr(t_statement *current, t_mini *mini)
{
	if (current->operator <= 2 && current->operator >= 1)
		rdr_out(current, mini);
	else if (current->operator == 3)
		mini->current = rdr_in(current, mini, -1);
	else if (current->operator == 4)
		rdr_in_until(current, mini);
}
