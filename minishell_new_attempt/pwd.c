/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatschu <smatschu@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 12:18:17 by ehedeman          #+#    #+#             */
/*   Updated: 2024/08/07 22:01:13 by smatschu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_pwd(void)
{
	char	*path;

	path = malloc(PATH_MAX + 1);
	if (!getcwd(path, PATH_MAX + 1))
		return (main_error(PATH_ERR));
	printf("%s\n", path);
	free(path);
	return (0);
}

int	check_pwd(t_statement *temp, t_mini *mini, int i)
{
	if (!ft_strncmp(temp->argv[i], "pwd", ft_strlen("pwd") + 1))
	{
		mini->exit_status = ft_pwd();
		return (1);
	}
	return (0);
}
