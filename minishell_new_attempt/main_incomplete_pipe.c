/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_incomplete_pipe.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatschu <smatschu@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 13:31:52 by ehedeman          #+#    #+#             */
/*   Updated: 2024/08/07 18:52:15 by smatschu         ###   ########.fr       */
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

int	complete_pipe(t_statement *temp)
{
	char	*complete;

	while (temp)
	{
		if (temp->operator == PIPE && !*temp->next->argv)
			break ;
		temp = temp->next;
	}
	complete = readline("> ");
	if (!complete)
		return (-1);
	free(temp->next->argv);
	free(temp->next);
	temp->next = parsing(complete);
	free(complete);
	return (0);
}
