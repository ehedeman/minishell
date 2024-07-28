/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_builtin_commands.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatschu <smatschu@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 16:47:10 by ehedeman          #+#    #+#             */
/*   Updated: 2024/07/28 18:53:38 by smatschu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_redirect_out(t_mini *mini)
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
			{
				close(fd);
				while ((mini->temp->next->operator == RDR_OUT_REPLACE || \
					mini->temp->next->operator == RDR_OUT_APPEND) && mini->temp->next)
				{
					fd = get_fd(mini->temp);
					if (mini->temp->next->operator == RDR_OUT_REPLACE || \
						mini->temp->next->operator == RDR_OUT_APPEND)
						close(fd);
					
				}
				break ;
			}
			else
			{
				mini->temp = mini->temp->next;
				return (fd);
			}
		}
		if (!mini->temp->next)
			break ;
		mini->temp = mini->temp->next;
	}
	return (fd);
}

static void	check_redirect_in(t_mini *mini)
{
	mini->invisible_file = 0;
	while (1)
	{
		if (mini->temp->operator == RDR_INPUT || \
			mini->temp->operator == RDR_INPUT_UNTIL)
		{
			if (mini->temp->next->operator != RDR_INPUT_UNTIL && \
				mini->temp->next->operator != RDR_INPUT)
			{
				redirect_in(mini->temp, mini);
				mini->temp = mini->temp->next;
				return ;
			}
		}
		else
			break ;
		if (!mini->temp->next)
			break ;
		mini->temp = mini->temp->next;
	}
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

static void	reset_std(t_mini *mini)
{
	reset_stdout(mini);
	reset_stdin(mini);
}

void	check_commands_loop(t_statement *temp, t_mini *mini, int i)
{
	// int	status;

	// status = 0;
	mini->fd_out = -1;
	mini->fd_in = -1;
	while (temp)
	{
		redirect_stdout(mini, check_redirect_out(mini));
		check_redirect_in(mini);
		if (command_involves_pipes(temp) && temp->operator <= 4 && temp->operator >= 1)
		{
			execute_pipeline(temp, mini);
			reset_std(mini);
			break ;
		}
		while (i < temp->argc && *temp->argv)
		{
			if (check_builtins(temp, mini, i))
				break ;
			if (check_execute(temp, i, mini))
				break ;
			i++;
		}
		i = 0;
		// while (temp->operator <= 4 && temp->operator >= 1 && temp->next)
		// 	temp = temp->next;
		temp = mini->temp;
		temp = temp->next;
		reset_std(mini);
		if (mini->invisible_file == 1)
			rm_invisible_file(mini, NULL);
	}
	//mini->exit_status = status;
}

int	check_builtins(t_statement *temp, t_mini *mini, int i)
{
	if (check_echo(temp, mini, i))
		return (1);
	if (check_cd(temp, mini, i))
		return (1);
	if (check_pwd(temp, mini, i))
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
