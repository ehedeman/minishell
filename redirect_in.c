/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:23:25 by ehedeman          #+#    #+#             */
/*   Updated: 2024/07/27 14:19:08 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	redirect_input(t_statement *temp)
{
	int		fd;

	fd = 0;
	if (temp->next)
		fd = open(temp->next->argv[0], O_RDONLY);
	if (fd < 0)
	{
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		write(2, "\n", 1);
	}
	return (fd);
}

int	redirect_input_until(t_statement *temp, t_mini *mini, int fd)
{
	char		*end_word;
	char		**input;
	int	i;

	i = 0;
	end_word = temp->next->argv[0];
	input = init_input();
	if (!input)
		return (-1);
	while (i < 1000)
	{
		input[i] = readline("> ");
		if (!input[i])
		{
			free_input(input);
			return (-1);
		}
		if (!strcmp(input[i], end_word))
			break ;
		i++;
	}
	free(input[i]);
	input[i] = NULL;
	copy_content(input); //creates invisible file, copies content
	if (fd < 0)
		return (1);
	free_input(input);
	fd = open(".temp_file", O_RDWR);
	if (temp->argv[0])
		redirect_stdin(mini, fd);
	mini->invisible_file = 1;
	return (0);
}

int	redirect_in(t_statement *temp, t_mini *mini)
{
	if (temp->operator == RDR_INPUT)
		redirect_stdin(mini, redirect_input(temp));
	else if (temp->operator == RDR_INPUT_UNTIL)
	{
		redirect_input_until(temp, mini, 0);
		return (1);
	}
	return (0);
}
