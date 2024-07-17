/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_builtin_commands.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatschu <smatschu@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 16:47:10 by ehedeman          #+#    #+#             */
/*   Updated: 2024/07/17 12:15:01 by smatschu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_redirect(t_mini *mini, t_statement *command)
{
	int	fd;

	fd = 1;
	while (1)
	{
		if (mini->temp->operator == RDR_OUT_REPLACE ||
			mini->temp->operator == RDR_OUT_APPEND)
		{
			fd = get_fd(mini->temp);
			if (mini->temp->next->operator == RDR_OUT_REPLACE ||
				mini->temp->next->operator == RDR_OUT_APPEND)
				close(fd);
			else
			{
				mini->temp = mini->temp->next;
				return (fd);
			}
		}
		else if (mini->temp->operator == RDR_INPUT ||
			mini->temp->operator == RDR_INPUT_UNTIL)
		{
			if (mini->temp->next->operator != RDR_INPUT_UNTIL &&
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
	if (!ft_strncmp(temp->argv[i], "./", 2)
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

// static t_statement	*check_pipe(t_statement *temp)
// {
// 	if (mini->temp->operator == PIPE)
// 	{
// 		do the pipe thing;

// 		check_builtins;
// 		check_execute;
		
// 		run the other pipe 
// 	}
// 	temp = temp->next;
// 	return (temp);
// }

void	check_commands_loop(t_statement *temp, t_mini *mini, int fd, int i)
{
	while (temp)
	{
		check_for_dollar_quoted(temp);
		fd = check_redirect(mini, temp);
//		temp = check_pipe();
		while (i < temp->argc && *temp->argv && fd != -1)
		{
			if (check_builtins(temp, mini, i, fd))
				break ;
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
	if (!ft_strncmp(mini->com_tab->argv[i], "history", ft_strlen(mini->com_tab->argv[i])))
		ft_history(&(mini->history));
	else
		return (0);
	return (1);
}

int	check_builtins(t_statement *temp, t_mini *mini, int i, int fd)
{
	if (!ft_strncmp(temp->argv[i], "echo", ft_strlen(temp->argv[i])))
		ft_echo(mini, temp, fd, i);
	else if (!ft_strncmp(temp->argv[i], "cd", ft_strlen(temp->argv[i])))
		ft_cd(temp, i);
	else if (!ft_strncmp(temp->argv[i], "pwd", ft_strlen(temp->argv[i])))
		ft_pwd(fd);
	else if (!ft_strncmp(temp->argv[i], "exit", ft_strlen(temp->argv[i])))
		ft_exit(mini);
	else if (!ft_strncmp(temp->argv[i], "env", ft_strlen(temp->argv[i]))
		&& !temp->argv[i + 1])
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
		return (check_history(mini, i));
	return (1);
}
