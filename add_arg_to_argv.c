/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_arg_to_argv.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 12:26:55 by ehedeman          #+#    #+#             */
/*   Updated: 2024/08/11 16:07:10 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	copy_mini(t_statement *temp, char **add, int *i, int j)
{
	while (add[j])
	{
		temp->argv[*i] = malloc(sizeof(char) * ft_strlen(add[j]) + 1);
		if (!temp->argv[*i])
			return (1);
		ft_strlcpy(temp->argv[*i], add[j], ft_strlen(add[j]) + 1);
		*i += 1;
		j++;
	}
	return (0);
}

static int	copy_current(t_statement *current, t_statement *temp, int *i)
{
	int	j;

	j = 1;
	while (current->argv[j])
	{
		temp->argv[*i] = malloc(sizeof(char) * \
			ft_strlen(current->argv[j]) + 1);
		if (!temp->argv[*i])
			return (1);
		ft_strlcpy(temp->argv[*i], current->argv[j], \
			ft_strlen(current->argv[j]) + 1);
		*i += 1;
		j++;
	}
	return (0);
}

static int	copy_args(t_statement *current, t_statement *temp, int *i, \
	t_mini *mini)
{
	int	j;

	j = 0;
	temp->argv[0] = malloc(sizeof(char) * \
			ft_strlen(current->argv[0]) + 1);
	if (!temp->argv[0])
		return (1);
	ft_strlcpy(temp->argv[0], current->argv[0], \
		ft_strlen(current->argv[0]) + 1);
	*i += 1;
	if (copy_flags(temp, mini, i, &j))
		return (1);
	if (copy_current(current, temp, i))
		return (1);
	if (copy_mini(temp, mini->additional_args, i, j))
		return (1);
	return (0);
}

static void	correct_node_order(t_mini *mini, t_statement *temp, \
	t_statement *current)
{
	int	i;

	if (current->id == 0)
		mini->com_tab = temp;
	if (current->id != 0)
		current->previous->next = temp;
	if (current->next)
		current->next->previous = temp;
	i = 0;
	while (current->argv[i])
	{
		free(current->argv[i]);
		i++;
	}
	free(current->argv);
	free(current);
}

t_statement	*add_arg_to_argv(t_statement *current, t_mini *mini)
{
	t_statement	*temp;
	int			i;

	i = 0;
	temp = p_new_node(current->argc + \
		ft_find_array_size(mini->additional_args, 0) + 1);
	if (!temp)
		return (NULL);
	if (copy_args(current, temp, &i, mini))
		return (NULL);
	temp->argv[i] = NULL;
	temp->next = current->next;
	temp->previous = current->previous;
	temp->id = current->id;
	temp->argc = current->argc + ft_find_array_size(mini->additional_args, 0);
	temp->operator = current->operator;
	temp->pipe_fd[0] = current->pipe_fd[0];
	temp->pipe_fd[1] = current->pipe_fd[1];
	correct_node_order(mini, temp, current);
	free(mini->additional_args);
	mini->additional_args = NULL;
	return (temp);
}
