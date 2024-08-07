/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatschu <smatschu@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 11:23:16 by ehedeman          #+#    #+#             */
/*   Updated: 2024/08/07 18:44:09 by smatschu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_cd_nothing(void)
{
	if (chdir(getenv("HOME")) == -1)
		printf("minishell: %s\n", strerror(errno));
}

static int	check_args_cd(t_statement *temp)
{
	if (temp->argc > 2)
	{
		write(2, "minishell: cd: too many arguments.\n", 35);
		return (1);
	}
	return (0);
}

static int	ft_cd(t_statement *temp, int i)
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
				printf("minishell: %s\n", strerror(errno));
			free(new_path);
		}
		else
			if (chdir(temp->argv[i + 1]) == -1)
				printf("minishell: %s\n", strerror(errno));
	}
	free(current_path);
	return (0);
}

int	check_cd(t_statement *temp, t_mini *mini, int i)
{
	if (!ft_strncmp(temp->argv[i], "cd", ft_strlen("cd") + 1))
	{
		mini->exit_status = ft_cd(temp, i);
		return (1);
	}
	return (0);
}
