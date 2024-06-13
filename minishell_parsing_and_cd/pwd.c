/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 12:18:17 by ehedeman          #+#    #+#             */
/*   Updated: 2024/06/12 15:39:22 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_mini *mini)
{
	char	*path;

	path = malloc(PATH_MAX + 1);
	if (!getcwd(path, PATH_MAX + 1))
		return ;
	write(mini->fd, path, ft_strlen(path));
	if (mini->fd == 1)
		write (1, "\n", 1);
	free(path);
}
