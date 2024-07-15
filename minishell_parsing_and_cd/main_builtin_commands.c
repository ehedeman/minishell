/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_builtin_commands.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 16:47:10 by ehedeman          #+#    #+#             */
/*   Updated: 2024/07/15 19:23:42 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_commands_loop(t_statement *temp, t_mini *mini, int fd, int i)
{
	while (temp)
	{
		check_for_path_quoted(temp);
		fd = check_redirect(mini, temp); //standart is 1, if its got redirection then its set new
		while (i < temp->argc && *temp->argv && fd != -1)
		{
			i = check_builtins(temp, mini, i, fd);
			if (i == 1)
				break ;
			if (!ft_strncmp(temp->argv[i], "./", 2) || !ft_strncmp(temp->argv[i], "/", 1))
			{
				if (exec_file(temp, mini) == -1)
					exit(0);
				break ;
			}
			else
			{
				if (exec_command(temp, mini) == -1)
					exit(0);
			}
			i++;
		}
		i = 0;
		temp = mini->temp;
		if (fd != 1 && fd != 2)
			close(fd);
		temp = temp->next;
	}
	return (0);
}

int	check_builtins(t_statement *temp, t_mini *mini, int i, int fd) // needs to return i so other thing knows what word we're at
{
	if (!ft_strncmp(temp->argv[i], "echo", ft_strlen(temp->argv[i])))
		ft_echo(mini, temp, fd, i);
	else if (!ft_strncmp(temp->argv[i], "cd", ft_strlen(temp->argv[i])))
		ft_cd(temp, i);
	else if (!ft_strncmp(temp->argv[i], "pwd", ft_strlen(temp->argv[i])))
		ft_pwd(fd);
	else if (!ft_strncmp(temp->argv[i], "exit", ft_strlen(temp->argv[i])))
		ft_exit(mini);
	else if (!ft_strncmp(temp->argv[i], "env", ft_strlen(temp->argv[i])) && !temp->argv[i + 1])
		ft_print_env_lst(mini->env);
	else if (!ft_strncmp(temp->argv[i], "export", ft_strlen(temp->argv[i])))
		ft_export(mini);
	else if (!ft_strncmp(temp->argv[i], "unset", ft_strlen(temp->argv[i])))
	{
		while (temp->argv[i])
		{
			ft_unset(mini->env, temp->argv[i]);
			i++;
		}
	}
	else
		return (0);
	return (1);
}