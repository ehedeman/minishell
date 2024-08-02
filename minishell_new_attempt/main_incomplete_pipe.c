/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_incomplete_pipe.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 13:31:52 by ehedeman          #+#    #+#             */
/*   Updated: 2024/08/01 13:32:15 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_incomplete_pipe(t_statement *temp)
{
	while (temp)
	{
		if (temp->id && temp->previous->operator == PIPE && !*temp->argv)
			return (1);
		temp = temp->next;
	}
	return (0);
}

int complete_pipe(t_statement *temp)
{
	char *complete;

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
