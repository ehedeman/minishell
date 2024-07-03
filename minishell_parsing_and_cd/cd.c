/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 11:23:16 by ehedeman          #+#    #+#             */
/*   Updated: 2024/07/03 15:04:53 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_cd_nothing(void)
{
	if (chdir(getenv("HOME")) == -1)
		printf("%s\n", strerror(errno));
}

static int check_args_cd(t_statement *temp)
{
	if (temp->argc > 2)
	{
		write(2, "minishell: cd: too many arguments.\n", 35);
		return (1);
	}
	return (0);
}

int	ft_cd(t_statement *temp, int i)
{
	char	*current_path;
	char	*new_path;

	if (check_args_cd(temp))
		return (1);
	current_path = malloc(PATH_MAX + 1);
	if (!getcwd(current_path, PATH_MAX + 1))
		return (1);
	if (!temp->argv[i + 1])
		ft_cd_nothing();
	else
	{
		if (temp->argv[i][0] != '/')
		{
			new_path = ft_strjoin(current_path, temp->argv[i]);
			if (chdir(temp->argv[i + 1]) == -1)
				printf("%s\n", strerror(errno));
			free(new_path);
		}
		else
			if (chdir(temp->argv[i + 1]) == -1)
				printf("%s\n", strerror(errno));
	}
	free(current_path);
	return (0);
}