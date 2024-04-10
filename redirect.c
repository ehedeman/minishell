/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 11:59:00 by ehedeman          #+#    #+#             */
/*   Updated: 2024/04/10 12:53:02 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect(char *filename, char *input, int red_type)
{
	int	fd;

	fd = 0;
	if (red_type == 1)
		fd = open(filename,  O_RDWR | O_EXCL | O_CREAT | O_APPEND);
	if (red_type == 2)
		fd = open(filename,  O_RDWR | O_EXCL | O_CREAT);
	else if (red_type == 3)
		fd = open(filename, O_RDWR | O_CREAT | O_TRUNC);
	if (fd < 0)
	{
		printf("Error: Opening the file.\n");
		return ;
	}
	write(fd, input, ft_strlen(input));
	close(fd);
}