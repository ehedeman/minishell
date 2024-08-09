/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_check_command_after_file.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatschu <smatschu@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:28:14 by ehedeman          #+#    #+#             */
/*   Updated: 2024/08/07 22:24:15 by smatschu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_command_after_file_rdr_two(t_statement *current, \
	t_operator operator)
{
	while (current->operator == operator && current->next->next)
		current = current->next;
	if (current->next->argc > 1)
		return (1);
	return (0);
}

int	check_command_after_file_rdr(t_statement *current)
{
	if (!*current->argv)
	{
		if (current->operator <= 2 && current->operator >= 1)
		{
			while ((current->next->operator == RDR_OUT_REPLACE \
					|| current->next->operator == RDR_OUT_APPEND) \
						&& current->next->next)
				current = current->next;
			if (current->next->argc > 1 || !*current->next->argv)
				return (1);
		}
		else if (current->operator == 3)
		{
			if (check_command_after_file_rdr_two(current, 3))
				return (1);
		}
		else if (current->operator == 4)
		{
			if (check_command_after_file_rdr_two(current, 4))
				return (1);
		}
	}
	return (0);
}

int	check_shell(char *argv)
{
	if (!ft_strcmp(argv, "bash"))
		return (1);
	else if (!ft_strcmp(argv, "zsh"))
		return (1);
	else if (!ft_strcmp(argv, "sh"))
		return (1);
	else if (!ft_strcmp(argv, "fish"))
		return (1);
	else if (!ft_strcmp(argv, "tmux"))
		return (1);
	else if (!ft_strcmp(argv, "dash"))
		return (1);
	return (0);
}
