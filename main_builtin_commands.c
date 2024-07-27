/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_builtin_commands.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatschu <smatschu@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 16:47:10 by ehedeman          #+#    #+#             */
/*   Updated: 2024/07/26 21:34:28 by smatschu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_redirect_out(t_mini *mini)
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
		else
			break ;
		if (!mini->temp->next)
			break ;
		mini->temp = mini->temp->next;
	}
	return (fd);
}

int	check_redirect_in(t_mini *mini, t_statement *command)
{
	while (1)
	{
		if (mini->temp->operator == RDR_INPUT || \
			mini->temp->operator == RDR_INPUT_UNTIL)
		{
			if (mini->temp->next->operator != RDR_INPUT_UNTIL && \
				mini->temp->next->operator != RDR_INPUT)
			{
				redirect_input(command, mini->temp, mini);
				mini->temp = mini->temp->next;
				return (1);
			}
		}
		else
			break ;
		if (!mini->temp->next)
			break ;
		mini->temp = mini->temp->next;
	}
	return (0);
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

void	check_commands_loop(t_statement *temp, t_mini *mini, int redirected, int i)
{
	int	status;

	status = 0;
	mini->fd = -1;
	while (temp)
	{
		redirect_stdout(mini, check_redirect_out(mini));
		redirected = check_redirect_in(mini, temp);
		if (command_involves_pipes(temp))
		{
			execute_pipeline(temp, mini);
			break ;
		}
		check_for_dollar_quoted(temp);
		while (i < temp->argc && *temp->argv && !redirected)
		{
			if (check_builtins(temp, mini, i))
				break ;
			// if (!ft_strncmp(temp->argv[i], "\'$", 2))
			// 	remove_quotes_main(temp, i);
			if (check_execute(temp, i, mini))
				break ;
			i++;
		}
		i = 0;
		temp = mini->temp;
		reset_stdout(mini);
		temp = temp->next;
	}
	mini->exit_status = status;
}

int	check_builtins(t_statement *temp, t_mini *mini, int i)
{
	if (check_echo(temp, mini, i))
		return (1);
	if (check_cd(temp, i))
		return (1);
	if (check_pwd(temp, i))
		return (1);
	if (check_exit(temp, mini, i))
		return (1);
	if (check_env(temp, mini, i))
		return (1);
	if (check_export(temp, mini, i))
		return (1);
	if (check_unset(temp, mini, i))
		return (1);
	if (check_history(temp, mini, i))
		return (1);
	return (0);
}
