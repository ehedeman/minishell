/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatschu <smatschu@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 12:18:17 by ehedeman          #+#    #+#             */
/*   Updated: 2024/07/26 21:18:19 by smatschu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(void)
{
	char	*path;

	path = malloc(PATH_MAX + 1);
	if (!getcwd(path, PATH_MAX + 1))
		return (main_error(PATH_ERR));
	printf("%s\n", path);
	free(path);
	return (0);
}

int	check_pwd(t_statement *temp, int i)
{
	if (!ft_strncmp(temp->argv[i], "pwd", ft_strlen("pwd") + 1))
	{
		ft_pwd();
		return (1);
	}
	return (0);
}
