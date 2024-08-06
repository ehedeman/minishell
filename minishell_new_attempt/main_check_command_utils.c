/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_check_command_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 13:32:38 by ehedeman          #+#    #+#             */
/*   Updated: 2024/08/06 16:08:00 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_builtins(t_statement *current, t_mini *mini, int i)
{
	if (check_echo(current, mini, i))
		return (1);
	if (check_cd(current, mini, i))
		return (1);
	if (check_pwd(current, mini, i))
		return (1);
	if (check_exit(current, mini, i))
		return (1);
	if (check_env(current, mini, i))
		return (1);
	if (check_export(current, mini, i))
		return (1);
	if (check_unset(current, mini, i))
		return (1);
	if (check_history(current, mini, i))
		return (1);
	return (0);
}

static int	check_execute(t_statement *current, int i, t_mini *mini)
{
	if (!ft_strncmp(current->argv[i], "./", 2)
		|| !ft_strncmp(current->argv[i], "/", 1))
	{
		reset_std(mini);
		exec_file(current, mini, i);
		return (1);
	}
	else
	{
		exec_command(current, mini, i);
		return (1);
	}
	return (0);
}

int	find_command(t_statement *current, t_mini *mini)
{
	int	i;

	i = 0;
	if (current->id != 0 && (current->previous->operator <= 4
			&& current->previous->operator >= 1))
		i++;
	while (i < current->argc && *current->argv)
	{
		if (check_builtins(current, mini, i))
		{
			reset_std(mini);
			return (1);
		}
		if (check_execute(current, i, mini))
		{
			reset_std(mini);
			return (1);
		}
		i++;
	}
	return (0);
}
