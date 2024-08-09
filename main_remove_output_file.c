/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_remove_output_file.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatschu <smatschu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 16:13:31 by ehedeman          #+#    #+#             */
/*   Updated: 2024/08/09 14:07:02 by smatschu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_statement	*initialize_remove_node(void)
{
	t_statement	*temp;

	temp = p_new_node(2);
	if (!temp)
	{
		printf("minishell: system error.");
		return (NULL);
	}
	return (temp);
}

static int	set_remove_node_args(t_statement *temp, t_mini *mini)
{
	temp->argv[0] = malloc(sizeof(char) * 3);
	if (!temp->argv[0])
	{
		printf("minishell: system error.");
		return (0);
	}
	if (is_path_in_env(mini->env))
		ft_strlcpy(temp->argv[0], "rm", 3);
	else
		ft_strlcpy(temp->argv[0], "/bin/rm", 9);
	temp->argv[1] = malloc(sizeof(char) * (ft_strlen(mini->out_path) + 1));
	if (!temp->argv[1])
	{
		printf("minishell: system error.");
		return (0);
	}
	ft_strlcpy(temp->argv[1], mini->out_path, ft_strlen(mini->out_path) + 1);
	temp->argv[2] = NULL;
	return (1);
}

static t_statement	*create_remove_node(t_mini *mini)
{
	t_statement	*temp;

	temp = initialize_remove_node();
	if (!temp)
		return (NULL);
	if (!set_remove_node_args(temp, mini))
	{
		free(temp);
		return (NULL);
	}
	return (temp);
}

void	remove_output_file(t_mini *mini)
{
	t_statement	*rm_node;

	rm_node = create_remove_node(mini);
	exec_command(rm_node, mini, 0);
	free_node_input(rm_node, NULL);
}
