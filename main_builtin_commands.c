/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_builtin_commands.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 16:47:10 by ehedeman          #+#    #+#             */
/*   Updated: 2024/07/25 10:48:46 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_redirect(t_mini *mini, t_statement *command)
{
	int	fd;

	fd = 1;
	while (1)
	{
		if (mini->temp->operator == RDR_OUT_REPLACE || \
			mini->temp->operator == RDR_OUT_APPEND)
		{
			fd = get_fd(mini->temp);
			if (mini->temp->next->operator == RDR_OUT_REPLACE || \
				mini->temp->next->operator == RDR_OUT_APPEND)
				close(fd);
			else
			{
				mini->temp = mini->temp->next;
				return (fd);
			}
		}
		else if (mini->temp->operator == RDR_INPUT || \
			mini->temp->operator == RDR_INPUT_UNTIL)
		{
			if (mini->temp->next->operator != RDR_INPUT_UNTIL && \
				mini->temp->next->operator != RDR_INPUT)
			{
				redirect_input(command, mini->temp, mini);
				mini->temp = mini->temp->next;
				return (-1);
			}
		}
		else
			break ;
		if (!mini->temp->next)
			break ;
		mini->temp = mini->temp->next;
	}
	return (fd);
}

static int	check_execute(t_statement *temp, int i, t_mini *mini)
{
	if (!ft_strncmp(temp->argv[i], "./", 2) \
		|| !ft_strncmp(temp->argv[i], "/", 1))
	{
		exec_file(temp, mini);
		return (1);
	}
	else
	{
		exec_command(temp, mini);
		return (1);
	}
	return (0);
}

void	check_commands_loop(t_statement *temp, t_mini *mini, int fd, int i)
{
	while (temp)
	{
		if (command_involves_pipes(temp))
		{
			execute_pipeline(temp, mini);
			break ;
		}
		check_for_dollar_quoted(temp);
		fd = check_redirect(mini, temp);
		while (i < temp->argc && *temp->argv && fd != -1)
		{
			if (check_builtins(temp, mini, i, fd))
				break ;
			// if (!ft_strncmp(temp->argv[i], "\'$", 2))
			// 	remove_quotes_main(temp, i);
			if (check_execute(temp, i, mini))
				break ;
			i++;
		}
		i = 0;
		temp = mini->temp;
		if (fd != 1 && fd != 2)
			close(fd);
		temp = temp->next;
	}
}

int	check_history(t_mini *mini, int i)
{
	if (!ft_strncmp(mini->com_tab->argv[i], "history", \
		ft_strlen(mini->com_tab->argv[i])))
	{
		if (mini->com_tab->argv[i + 1])
		{
			printf("history: too many arguments\n");
			return (1);
		}
		ft_history(&(mini->history));
	}
	else
		return (0);
	return (1);
}

int	check_builtins(t_statement *temp, t_mini *mini, int i, int fd)
{
	if (!ft_strncmp(temp->argv[i], "echo", ft_strlen("echo") + 1))
		ft_echo(mini, temp, fd, i);
	else if (!ft_strncmp(temp->argv[i], "cd", ft_strlen("cd") + 1))
		ft_cd(temp, i);
	else if (!ft_strncmp(temp->argv[i], "pwd", ft_strlen("pwd") + 1))
		ft_pwd(fd);
	else if (!ft_strncmp(temp->argv[i], "exit", ft_strlen("exit") + 1))
		ft_exit(mini);
	else if (!ft_strncmp(temp->argv[i], "env", ft_strlen("env") + 1) \
		&& !temp->argv[i + 1])
		ft_print_env_lst(mini->env);
	else if (!ft_strncmp(temp->argv[i], "export", ft_strlen("export") + 1))
		ft_export(mini);
	else if (!ft_strncmp(temp->argv[i], "unset", ft_strlen("unset") + 1))
	{
		while (temp->argv[i])
		{
			ft_unset(mini->env, temp->argv[i]);
			i++;
		}
	}
	else if (!ft_strncmp(temp->argv[i], "history", ft_strlen("history") + 1))
		check_history(mini, i);
	else
		return (0);
	return (1);
}
