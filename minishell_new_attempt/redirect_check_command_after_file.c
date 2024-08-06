/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_check_command_after_file.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 15:28:14 by ehedeman          #+#    #+#             */
/*   Updated: 2024/08/06 16:17:59 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_command_after_file_rdr_2(t_statement *current, \
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
			while ((current->operator == RDR_OUT_REPLACE \
					|| current->operator == RDR_OUT_APPEND) \
						&& current->next->next)
				current = current->next;
			if (current->next->argc > 1)
				return (1);
		}
		else if (current->operator == 3)
		{
			if (check_command_after_file_rdr_2(current, 3))
				return (1);
		}
		else if (current->operator == 4)
		{
			if (check_command_after_file_rdr_2(current, 4))
				return (1);
		}
	}
	return (0);
}
