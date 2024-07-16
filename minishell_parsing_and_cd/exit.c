/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:12:06 by ehedeman          #+#    #+#             */
/*   Updated: 2024/07/16 13:04:19 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_com_tab(t_mini *mini)
{
	t_statement	*temp;
	t_statement	*next;
	int	i;

	i = 0;
	temp = mini->com_tab;
	while(temp)
	{
		next = temp->next;
		i = 0;
		while (i < temp->argc)
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
	rl_clear_history();
	printf("Bye then :)\n");
	exit(0);
}

