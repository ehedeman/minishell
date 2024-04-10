/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 12:18:17 by ehedeman          #+#    #+#             */
/*   Updated: 2024/04/10 14:25:23 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_mini *mini)
{
	char	*path;

	path = malloc(PATH_MAX + 1);
	if (!getcwd(path, PATH_MAX + 1))
		return ;
	write(mini->redirect, path, ft_strlen(path));
	free(path);
}
