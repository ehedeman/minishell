/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_find_and_set_redirections.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatschu <smatschu@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 14:56:39 by ehedeman          #+#    #+#             */
/*   Updated: 2024/08/04 19:30:09 by smatschu         ###   ########.fr       */
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
		{
			fd = get_fd(current);
			if (current->next && (current->next->operator == 1
				|| current->next->operator == 2))
				close(fd);
		}
		else if (current->operator != 1 && current->operator != 2)
			break ;
		current = current->next;
	}
	redirect_stdout(mini, fd, 0);
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
			fd = redirect_input(current); //open file
			if (fd == -1) //nessecary cuz if file doesnt exist then all stops
				return (1);
			if (current->next && current->next->operator == 3)
				close(fd);
		}
		if (current->operator != 3)
			break ;
		current = current->next;
	}
	redirect_stdin(mini, fd, 0); //sets stdin to file of last
	if (current->operator == NONE)
		mini->current = current->next;
	else
		mini->current = current;
	return (0);
}

void	find_and_set_last_redirect_in_until(t_statement *current, t_mini *mini)
{
//	int		count;
	char	*end_word;

//	count = 0;
	end_word = NULL;
	if (current->next)
		end_word = current->next->argv[0];;
	current = redirect_input_until(current, end_word, mini);
	if (current->operator == NONE)
		mini->current = current->next;
	else
		mini->current = current;
}
//needs to be redone