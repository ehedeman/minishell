/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_std.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 11:19:24 by ehedeman          #+#    #+#             */
/*   Updated: 2024/07/27 14:55:41 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_stdin(t_mini *mini, int fd)
{
	if (fd != 0 && fd != -1)
	{
		mini->stdin_copy = dup(0);
		close(0);
		mini->fd_in = dup2(fd, 0);
		if (mini->fd_in < 0)
		{
			close(fd);
			write(1, strerror(errno), ft_strlen(strerror(errno)));
		}
		return (1);
	}
	return (0);
}

int reset_stdin(t_mini *mini)
{
	if (mini->fd_in == 0)
		dup2(mini->stdin_copy, 0);
	mini->fd_in = -1;
	return (0);
}

int	redirect_stdout(t_mini *mini, int fd)
{
	if (fd != 1 && fd != -1)
	{
		mini->stdout_copy = dup(1);
		close(1);
		mini->fd_out = dup2(fd, 1);
		if (mini->fd_out < 0)
		{
			close(fd);
			write(1, strerror(errno), ft_strlen(strerror(errno)));
		}
	}
	return (0);
}

int reset_stdout(t_mini *mini)
{
	if (mini->fd_out == 1)
		dup2(mini->stdout_copy, 1);
	mini->fd_out = -1;
	return (0);
}