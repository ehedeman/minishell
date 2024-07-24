/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatschu <smatschu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:12:06 by ehedeman          #+#    #+#             */
/*   Updated: 2024/07/24 17:59:03 by smatschu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_com_tab(t_mini *mini)
{
	t_statement	*temp;
	t_statement	*next;
	int			i;

	i = 0;
	temp = mini->com_tab;
	while (temp)
	{
		next = temp->next;
		i = 0;
		while (temp->argv[i])
		{
			free(temp->argv[i]);
			i++;
		}
		free(temp->argv);
		free(temp);
		temp = next;
	}
}

void	ft_exit(t_mini *mini)
{
	free_com_tab(mini);
	ft_env_lst_clear(mini->env, free);
	free_history(&(mini->history));
	rl_clear_history();
	printf("Bye then :)\n");
	exit(0);
}
