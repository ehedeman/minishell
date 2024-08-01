/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_find_and_set_redirections.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 14:56:39 by ehedeman          #+#    #+#             */
/*   Updated: 2024/08/01 15:12:44 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	find_and_set_last_redirect_out(t_statement *current, t_mini *mini)
{
	int	fd;

	fd = -1;
	while (current)
	{
		if (current->operator == 1 || current->operator == 2)
			fd = get_fd(current);
		else if (current->operator != 1 && current->operator != 2)
			break ;
		current = current->next;
	}
	redirect_stdout(mini, fd);
	mini->current = current;
}

int	find_and_set_last_redirect_in(t_statement *current, t_mini *mini)
{
	int fd;

	fd = -1;
	while (current)
	{
		if (current->operator == 3)
		{
			fd = redirect_input(current, mini) //open file
			if (fd == -1) //nessecary cuz if file doesnt exist then all stops
				return (1);
		}
		if (current->operator != 3)
			break ;
		current = current->next;
	}
	redirect_stdin(mini, fd); //sets stdin to file of last
	mini->current = current;
	return (0);
}

void	find_and_set_last_redirect_in_until(t_statement *current, t_mini *mini)
{
	int		count;
	char	*end_word;

	count = 0;
	end_word = NULL;
	while (current)
	{
		if (current->operator == 4)
		{
			count++;
			end_word = temp->argv[0];
		}
		else if (current->operator != 4)
			break ;
		current = current->next;
	}
	if (count > 1)
		redirect_input_until(current, end_word, mini, 1) //sets the stdin to empty file (test wc -l << end << blah)
	else if (count == 1)
		redirect_input_until(current, end_word, mini, 0);//sets stdin to the temp file with content
	mini->current = current;
}
