/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_builtin_commands.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 16:47:10 by ehedeman          #+#    #+#             */
/*   Updated: 2024/07/15 15:27:53 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static int	compare()
// {
	
// }

int	check_commands_loop(t_statement *temp, t_mini *mini, int fd, int i)
{
	while (temp)
	{
		fd = check_redirect(mini, temp); //standart is 1, if its got redirection then its set new
		while (i < temp->argc && *temp->argv && fd != -1)
		{
			i = check_builtins(temp, mini, i, fd);
			if (i >= temp->argc)
				break ;
			if (!ft_strncmp(temp->argv[i], "./", 2) || !ft_strncmp(temp->argv[i], "/", 1))
			{
				if (exec_file(temp, mini) == -1)
					return (-1);
				break ;
			}
			else if (temp->operator != SKIP)
			{
				if (exec_command(temp, mini) == -1)
					return (-1);
				return (0);
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
	if (ft_strncmp(temp->argv[i], "echo", 4) == 0)
	{
		ft_echo(temp, fd, i);
		i = temp->argc;
	}
	else if (ft_strncmp(temp->argv[i], "cd", 2) == 0)
	{
		if (ft_cd(temp, i))
			i = temp->argc;
		if (temp->argv[i + 1])
			i++;
	} //skips the path after use
	else if (ft_strncmp(temp->argv[i], "pwd", 3) == 0)
		ft_pwd(fd);
	else if (ft_strncmp(temp->argv[i], "exit", 5) == 0)
		ft_exit(mini);
	else if (ft_strncmp(temp->argv[i], "env", 3) == 0 && !temp->argv[i + 1])
		return (ft_print_env_lst(mini->env));
	else if (ft_strncmp(temp->argv[i], "export", 6) == 0)
	{
		//return(ft_export(mini));
		ft_export(mini);
		// printf("LIST AFTER EXPORT:\n");
		// ft_print_env_lst(mini->env);
		i = temp->argc;
	}
	else if (ft_strncmp(temp->argv[i], "unset", 5) == 0)
	{
		while (temp->argv[i])
		{
			ft_unset(mini->env, temp->argv[i]);
			i++;
		}
		i = temp->argc;
	}
	i++;
	return (i);
}