/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_builtin_commands.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 16:47:10 by ehedeman          #+#    #+#             */
/*   Updated: 2024/07/30 12:56:02 by ehedeman         ###   ########.fr       */
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
			if (mini->temp->next && (mini->temp->next->operator == RDR_OUT_REPLACE || \
				mini->temp->next->operator == RDR_OUT_APPEND))
			{
				close(fd);
				mini->temp = mini->temp->next;
				while ((mini->temp->operator == RDR_OUT_REPLACE || \
					mini->temp->operator == RDR_OUT_APPEND) && mini->temp)
				{
					fd = get_fd(mini->temp);
					if (mini->temp->next->operator == RDR_OUT_REPLACE || \
						mini->temp->next->operator == RDR_OUT_APPEND)
						close(fd);
					else
						break ;
					mini->temp = mini->temp->next;
				}
				continue ;
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
static void	check_redirect_in(t_mini *mini, t_statement *temp)
{
	mini->invisible_file = 0;
	mini->temp = temp;
	while (1)
	{
		while (mini->temp->operator == RDR_INPUT || \
			mini->temp->operator == RDR_INPUT_UNTIL)
		{
			if (mini->temp->next->operator != RDR_INPUT_UNTIL && \
				mini->temp->next->operator != RDR_INPUT)
			{
				redirect_in(mini->temp, mini);
				mini->temp = mini->temp->next;
				return ;
			}
			mini->temp = mini->temp->next;
		}
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
		exec_command(temp, mini, i);
		return (1);
	}
	return (0);
}

static void	reset_std(t_mini *mini)
{
	reset_stdout(mini);
	reset_stdin(mini);
}

int	check_incomplete_pipe(t_statement *temp)
{
	while (temp)
	{
		if (temp->id && temp->previous->operator == PIPE && !*temp->argv)
			return (1);
		temp = temp->next;
	}
	return (0);
}

int	complete_pipe(t_statement *temp)
{
	char *complete;

	while (temp)
	{
		if (temp->operator == PIPE && !*temp->next->argv)
			break ;
		temp = temp->next;
	}
	complete = readline("> ");
	if (!complete)
		return (-1);
	free(temp->next->argv);
	free(temp->next);
	temp->next = parsing(complete);
	free(complete);
	return (0);
}

void	check_commands_loop(t_statement *temp, t_mini *mini, int i)
{
	// int	status;

	// status = 0;
	mini->fd_out = -1;
	mini->fd_in = -1;
	if (check_incomplete_pipe(temp))
		complete_pipe(temp);
	redirect_stdout(mini, check_redirect_out(mini));
	while (temp)
	{
		if (temp->previous && temp->previous->operator == PIPE && (temp->operator == 1 || temp->operator == 2))
			redirect_stdout(mini, check_redirect_out(mini));
		check_redirect_in(mini, temp);
		if (command_involves_pipes(temp))
		{
			execute_pipeline(temp, mini);
			reset_std(mini);
			break ;
		}
		if (temp->id != 0 && (temp->previous->operator <= 4 && temp->previous->operator >= 1))
			i++;
		while (i < temp->argc && *temp->argv)
		{
			if (check_builtins(temp, mini, i))
			{
				reset_std(mini);
				break ;
			}	
			if (check_execute(temp, i, mini))
			{
				reset_std(mini);
				break ;
			}
			i++;
		}
		i = 0;
		if (temp->operator < 5 && temp->operator > 0)
			temp = mini->temp;
		else if (temp->operator == 5 || temp->operator == 0)
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
