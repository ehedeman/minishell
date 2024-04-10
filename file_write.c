/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_write.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 11:59:00 by ehedeman          #+#    #+#             */
/*   Updated: 2024/04/10 14:40:10 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	file_write(char *filename, char *input, int red_type, t_mini *mini)
{
	int	fd;

	fd = 0;
	if (red_type == 1)
		fd = open(filename,  O_RDWR | O_APPEND, mini->mode);
	if (red_type == 2)
		fd = open(filename,  O_RDWR | O_CREAT, mini->mode);
	else if (red_type == 3)
		fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, mini->mode);
	if (fd < 0)
	{
		printf("Error: Opening the file.\n");
		return ;
	}
	write(fd, input, ft_strlen(input));
	close(fd);
}

int	create_file(char *filename, t_mini *mini)
{
	int	fd;

	fd = open(filename, O_RDWR | O_CREAT, mini->mode);
	if (fd < 0)
	{
		printf("Error: Opening the file.\n");
		return (0);
	}
	return (fd);
}