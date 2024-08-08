/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_in_until_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 12:09:40 by ehedeman          #+#    #+#             */
/*   Updated: 2024/08/08 14:54:59 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	copy_content(char **input)
{
	int		fd;
	mode_t	mode;
	int		i;

	i = 0;
	mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	fd = open(".temp_file", O_RDWR | O_CREAT | O_TRUNC, mode);
	if (fd < 0)
	{
		printf("minishell: system error.");
		return (-1);
	}
	if (!input)
		return (fd);
	while (input[i])
	{
		write(fd, input[i], ft_strlen(input[i]));
		write(fd, "\n", 1);
		i++;
	}
	close(fd);
	return (0);
}

t_statement	*create_rm_node(void)
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
	temp->argv[1] = malloc(sizeof(char) * (ft_strlen(".temp_file") + 1));
	if (!temp->argv[1])
	{
		printf("minishell: system error.");
		return (NULL);
	}
	ft_strlcpy(temp->argv[1], ".temp_file", ft_strlen(".temp_file") + 1);
	temp->argv[2] = NULL;
	return (temp);
}

char	**init_input(void)
{
	char	**input;

	input = malloc(sizeof(char *) * 1000);
	if (!input)
	{
		printf("minishell: system error.");
		return (NULL);
	}
	input[0] = NULL;
	return (input);
}

int	condition_from_get_input(char **input, int *i)
{
	if (!input[*i] || g_sig == 3)
	{
		g_sig = 0;
		free_input(input, *i);
		return (1);
	}
	return (0);
}
