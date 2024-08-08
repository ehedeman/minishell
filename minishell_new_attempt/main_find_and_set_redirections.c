/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_find_and_set_redirections.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 14:56:39 by ehedeman          #+#    #+#             */
/*   Updated: 2024/08/08 13:01:12 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	copy_args(t_mini *mini, t_statement *current)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	mini->additional_args = malloc(sizeof(char *) * \
		(ft_find_array_size(current->argv, 1) + 1));
	if (!mini->additional_args)
		return ;
	while (current->argv[i])
	{
		mini->additional_args[j] = current->argv[i];
		j++;
		i++;
	}
	mini->additional_args[j] = NULL;
}

int	find_and_set_last_redirect_out(t_statement *current, t_mini *mini)
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
		if (current->next && current->next->argc > 1)
			copy_args(mini, current->next);
		current = current->next;
	}
	if (current->operator == NONE)
		mini->current = current->next;
	else
		mini->current = current;
	return (fd);
}

int	find_and_set_last_redirect_in(t_statement *current, t_mini *mini)
{
	int	fd;

	fd = -1;
	while (current)
	{
		if (current->operator == 3)
		{
			fd = redirect_input(current);
			if (fd == -1)
				return (1);
			if (current->next && current->next->operator == 3)
				close(fd);
		}
		if (current->operator != 3)
			break ;
		if (current->next && current->next->argc > 1)
			copy_args(mini, current->next);
		current = current->next;
	}
	redirect_stdin(mini, fd, 0);
	if (current->operator == NONE)
		mini->current = current->next;
	else
		mini->current = current;
	return (0);
}

void	find_and_set_last_redirect_in_until(t_statement *current, t_mini *mini)
{
	char	*end_word;

	end_word = NULL;
	if (current->next)
		end_word = current->next->argv[0];
	if (current->next && current->next->argc > 1)
		copy_args(mini, current->next);
	current = redirect_input_until(current, end_word, mini);
	if (!current)
		mini->current = current;
	else if (current->operator == NONE)
		mini->current = current->next;
	else
		mini->current = current;
}
