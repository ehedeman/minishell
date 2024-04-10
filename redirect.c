/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 11:59:00 by ehedeman          #+#    #+#             */
/*   Updated: 2024/04/10 13:19:56 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect(char *filename, char *input, int red_type)
{
	int	fd;
	mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;

	fd = 0;
	if (red_type == 1)
		fd = open(filename,  O_RDWR | O_APPEND, mode);
	if (red_type == 2)
		fd = open(filename,  O_RDWR | O_CREAT, mode);
	else if (red_type == 3)
		fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, mode);
	if (fd < 0)
	{
		printf("Error: Opening the file.\n");
		return ;
	}
	write(fd, input, ft_strlen(input));
	close(fd);
}