/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:23:25 by ehedeman          #+#    #+#             */
/*   Updated: 2024/07/12 15:38:31 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	reset_stdin(int old_fd)
{
	if (dup2(0 , old_fd) < 0)
		return (main_error(-1));
	close(old_fd);
	return (0);
}

static int	redirect_in(t_statement *command, t_statement *temp, t_mini *mini)
{
	int fd_cpy;
	int fd;
	pid_t	pid;
	int	status;

	if (!*temp->argv)
		return (-1);
	pid = fork();
	if (pid == -1)
		return (main_error(-1));
	else if (pid == 0)
	{
		fd = open(temp->next->argv[0], O_RDONLY);
		if (fd < 0)
		{
			printf("minishell: %s\n", strerror(errno));
			exit(0);
		}
		command->next = temp;
		fd_cpy = dup2(fd, 0);
		if (fd_cpy < 0)
		{
			close (fd);
			exit(0);
		}
		exec_command(command, mini);
		if (reset_stdin(fd) < 0)
			exit(0);
		exit(0);
	}
	else
		waitpid(pid, &status, 0);
	return (0);
}
//works, loops for some reason 
static int	redirect_in_until(t_statement *temp)
{
	temp = temp->next;
	return (0);
}

int	redirect_input(t_statement *command, t_statement *temp, t_mini *mini)
{
	if (temp->operator == RDR_INPUT)
		return (redirect_in(command, temp, mini));
	if (temp->operator == RDR_INPUT_UNTIL)
		return (redirect_in_until( temp));
	return (1);
}
//returns 1 so the fd is still 1 (makes sense cuz this is called by)
//check_redirect and that returns a fd.