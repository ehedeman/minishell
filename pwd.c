/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 12:18:17 by ehedeman          #+#    #+#             */
/*   Updated: 2024/07/03 15:13:16 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(int fd)
{
	char	*path;

	if (fd < 0)
		return (0);
	path = malloc(PATH_MAX + 1);
	if (!getcwd(path, PATH_MAX + 1))
		return (main_error(PATH_ERR));
	write(fd, path, ft_strlen(path));
	if (fd == 1 || fd == 2)
		write (fd, "\n", 1);
	free(path);
	return (0);
}
