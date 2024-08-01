/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:11:09 by ehedeman          #+#    #+#             */
/*   Updated: 2024/07/29 12:21:58 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_history(t_history *history)
{
	int	i;

	i = 0;
	if (history->commands)
	{
		while (i < history->capacity)
		{
			free(history->commands[i]);
			i++;
		}
		free(history->commands);
		history->commands = NULL;
	}
}

//capacity in bash is 2000, try echo $HISTFILESIZE
void	init_history(t_history *history)
{
	int	i;

	i = 0;
	history->capacity = 5;
	history->commands = malloc(history->capacity * sizeof(char *));
	if (!history->commands)
		perror("history malloc");
	history->size = 0;
	history->oldest = 0;
	history->total = 0;
	while (i < history->capacity)
	{
		history->commands[i] = NULL;
		i++;
	}
}

void	add_to_hist_arr(t_history *history, char *command)
{
	int		i;
	int		last_i;
	char	*last_command;

	if (history->size > 0)
	{
		last_i = (history->oldest + history->size - 1) % history->capacity;
		last_command = history->commands[last_i];
		if (ft_strcmp(last_command, command) == 0)
			return ;
	}
	history->total++;
	if (history->size >= history->capacity)
	{
		free(history->commands[history->oldest]);
		history->commands[history->oldest] = ft_strdup(command);
		history->oldest = (history->oldest + 1) % history->capacity;
	}
	else
	{
		i = (history->oldest + history->size) % history->capacity;
		history->commands[i] = ft_strdup(command);
		history->size++;
	}
}

void	ft_history(const t_history *history)
{
	int	count;
	int	i;
	int	start;

	if (history->total > history->capacity)
		start = history->total - history->capacity + 1;
	else
		start = 1;
	count = 0;
	i = history->oldest;
	while (count < history->size)
	{
		printf("%d %s\n", start, history->commands[i]);
		i = (i + 1) % history->capacity;
		count++;
		start++;
	}
}

int	check_history(t_statement *temp, t_mini *mini, int i)
{
	if (!ft_strncmp(temp->argv[i], "history", ft_strlen("history") + 1))
	{
		if (temp->argv[i + 1])
		{
			printf("history: too many arguments\n");
			return (1);
		}
		ft_history(&(mini->history));
		return (1);
	}
	return (0);
}
