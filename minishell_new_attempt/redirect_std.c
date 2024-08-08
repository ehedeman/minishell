/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_std.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 11:19:24 by ehedeman          #+#    #+#             */
/*   Updated: 2024/08/08 14:38:04 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_std(t_mini *mini)
{
	reset_stdout(mini);
	reset_stdin(mini);
}

int	redirect_stdin(t_mini *mini, int fd, int mode)
{
	if (fd != 0 && fd != -1)
	{
		if (!mode)
		{
			mini->stdin_copy = dup(0);
			close(0);
			mini->fd_in = dup2(fd, 0);
			close(fd);
			if (mini->fd_in < 0)
				write(2, strerror(errno), ft_strlen(strerror(errno)));
		}
		else
		{
			close(0);
			mini->fd_in = dup2(fd, 0);
			close(fd);
			if (mini->fd_in < 0)
				write(2, strerror(errno), ft_strlen(strerror(errno)));
		}
		return (1);
	}
	return (-1);
}

int	reset_stdin(t_mini *mini)
{
	if (mini->fd_in == 0)
	{
		close(0);
		dup2(mini->stdin_copy, 0);
		close(mini->stdin_copy);
	}
	mini->fd_in = -1;
	return (0);
}

int	redirect_stdout(t_mini *mini, int fd, int mode)
{
	if (fd != 1 && fd != -1)
	{
		if (!mode)
		{
			mini->stdout_copy = dup(1);
			close(1);
			mini->fd_out = dup2(fd, 1);
			close(fd);
			if (mini->fd_out < 0)
				write(2, strerror(errno), ft_strlen(strerror(errno)));
		}
		else
		{
			close(1);
			mini->fd_out = dup2(fd, 1);
			close(fd);
			if (mini->fd_out < 0)
				write(2, strerror(errno), ft_strlen(strerror(errno)));
		}
		return (1);
	}
	return (-1);
}

int	reset_stdout(t_mini *mini)
{
	if (mini->fd_out == 1)
	{
		close(1);
		dup2(mini->stdout_copy, 1);
		close(mini->stdout_copy);
	}
	mini->fd_out = -1;
	return (0);
}
