/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:23:25 by ehedeman          #+#    #+#             */
/*   Updated: 2024/08/01 15:40:38 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	rm_invisible_file(t_mini *mini, char **input)
{
    t_statement *rm_node;

	rm_node = create_rm_node(); // creates node with rm and invisible file name
	exec_command(rm_node, mini, 0);
	free_node_input(rm_node, input);
}

int	redirect_input(t_statement *current)
{
	int		fd;

	fd = 0;
	if (current->next)
		fd = open(current->next->argv[0], O_RDONLY);
	if (fd < 0)
	{
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		write(2, "\n", 1);
		return (-1);
	}
	return (fd);
}

static int	get_input(char **input, char *end_word)
{
	int	i;

	i = 0;
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
	return (i);
}

int	redirect_input_until(t_statement *current, char *end_word,\
		t_mini *mini, int mode)
{
	char		**input;
	int			i;
	int			fd;
	
	input = init_input(); //malloc of input
	if (!input)
		return (-1);
	i = get_input(input, end_word); //readline part in there
	if (i == -1)
		return (-1);
	free(input[i]); //free end word part of input
	input[i] = NULL;
	copy_content(input); //creates invisible file, copies content
	free_input(input); //no longer needed
	if (mode)
		fd = copy_content(NULL); //empties the file cuz if theres more than one its always 0 (e.g wc -l)
	else
		fd = open(".temp_file", O_RDWR); //just opens the file regularly to read from it
	if (fd < 0)
			return (1);
	if (current->argv[0])
		redirect_stdin(mini, fd); //automatically sets file as stdin as it should
	mini->invisible_file = 1;
	return (0);
}