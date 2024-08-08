/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:23:25 by ehedeman          #+#    #+#             */
/*   Updated: 2024/08/08 14:59:20 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	rm_invisible_file(t_mini *mini, char **input)
{
	t_statement	*rm_node;

	rm_node = create_rm_node();
	exec_command(rm_node, mini, 0);
	free_node_input(rm_node, input);
	mini->invisible_file = 0;
}

int	redirect_input(t_statement *current)
{
	int	fd;

	fd = 0;
	if (current->next)
		fd = open(current->next->argv[0], O_RDONLY);
	if (fd < 0)
	{
		perror(current->next->argv[0]);
		return (-1);
	}
	return (fd);
}

static void	clear_input(char **input, int i)
{
	int	j;

	j = 0;
	while (j <= i)
	{
		free(input[j]);
		j++;
	}
}

static t_statement	*get_input(char **input, char *end_word, \
								t_statement *current, int *i)
{
	current = current->next;
	g_sig = 2;
	while (*i < 1000 && g_sig != 3)
	{
		input[*i] = readline("> ");
		if (condition_from_get_input(input, i))
			return (NULL);
		if (!ft_strcmp(input[*i], end_word))
		{
			if (current->next && current->operator == 4)
			{
				clear_input(input, *i);
				*i = 0;
				current = current->next;
				end_word = current->argv[0];
				continue ;
			}
			else
				break ;
		}
		*i += 1;
	}
	g_sig = 0;
	return (current);
}

t_statement	*redirect_input_until(t_statement *current, char *end_word, \
		t_mini *mini)
{
	char		**input;
	int			i;
	int			fd;

	i = 0;
	input = init_input();
	if (!input)
		return (NULL);
	current = get_input(input, end_word, current, &i);
	if (!current)
		return (NULL);
	free(input[i]);
	input[i] = NULL;
	copy_content(input);
	free_input(input, -1);
	fd = open(".temp_file", O_RDWR);
	if (fd < 0)
		return (NULL);
	redirect_stdin(mini, fd, 0);
	mini->invisible_file = 1;
	return (current);
}
