/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_remove_output_file.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 16:13:31 by ehedeman          #+#    #+#             */
/*   Updated: 2024/08/06 13:03:21 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_statement	*create_remove_node(void)
{
	t_statement	*temp;

	temp = p_new_node(2);
	if (!temp)
	{
		printf("minishell: system error.");
		return (NULL);
	}
	temp->argv[0] = malloc(sizeof(char) * 3);
	if (!temp->argv[0])
	{
		printf("minishell: system error.");
		return (NULL);
	}
	ft_strlcpy(temp->argv[0], "rm", 3);
	temp->argv[1] = malloc(sizeof(char) * (ft_strlen(".output") + 1));
	if (!temp->argv[1])
	{
		printf("minishell: system error.");
		return (NULL);
	}
	ft_strlcpy(temp->argv[1], ".output", ft_strlen(".output") + 1);
	temp->argv[2] = NULL;
	return (temp);
}

void	remove_output_file(t_mini *mini)
{
	t_statement	*rm_node;

	rm_node = create_remove_node(); // creates node with rm and invisible file name
	exec_command(rm_node, mini, 0);
	free_node_input(rm_node, NULL);
}
