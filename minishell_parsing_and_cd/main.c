/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 10:57:19 by ehedeman          #+#    #+#             */
/*   Updated: 2024/07/08 10:09:25 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sig;

//if theres multiple output redirections it creates all of the files, then
//closes them if nessecary.
//returns only the last fd.
// (get_fd is for creating the right type of file if nessecary. else it just
//  opens the right file)
//test github
int	check_redirect_output(t_mini *mini)
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
		}
		else if (mini->temp->operator > RDR_OUT_APPEND || mini->temp->operator == NONE)
			break ;
		if (!mini->temp->next)
			break ;
		mini->temp = mini->temp->next;
	}
	return (fd);
}

int	check_command(t_mini *mini)
{
	t_statement *temp;
	int fd;
	int	i;

	mini->temp = mini->com_tab;
	temp = mini->temp;
	while (temp)
	{
		i = 0;
		fd = check_redirect_output(mini); //standart is 1, if its got redirection then its set new
		while (i < temp->argc)
		{
			if (!ft_strncmp(temp->argv[i], "./", 2) || !ft_strncmp(temp->argv[i], "/", 1))
			{
				if (exec_file(temp) == -1)
					return (-1);
				break ;
			}
			if (ft_strncmp(temp->argv[i], "cd", 2) == 0)
			{
				if (ft_cd(temp, i))
					return (0);
				if (temp->argv[i + 1])
					i++;
			} //skips the path after use
			else if (ft_strncmp(temp->argv[i], "pwd", 3) == 0)
				ft_pwd(fd);
			else if (ft_strncmp(temp->argv[i], "exit", 5) == 0)
				ft_exit(mini);
			else if (ft_strncmp(temp->argv[i], "print", 5) == 0)
			{
				ft_print(mini, temp);
				if (temp->operator == NONE)
					return (0);
			}
			else if (ft_strncmp(temp->argv[i], "echo", 4) == 0)
			{
				ft_echo(temp, fd, i);
				break ;
			}
			else if (ft_strncmp(temp->argv[i], "env", 3) == 0 && !temp->argv[i + 1])
				return (ft_print_env_lst(mini->env));
			else if (ft_strncmp(temp->argv[i], "rm", 2) == 0)
			{
				ft_rm(temp);
				return (0);
			}
			else if (temp->operator != SKIP)
			{
				write(1, "Command not found.\n", 19);
				return (0);
			}
			i++;
		}
		temp = mini->temp;
		if (fd != 1 && fd != 2)
			close(fd);
		temp = temp->next;
	}
	return (0);
}

void	handler(int sig)
{
	g_sig = sig;
}

int main (int argc, char **argv, char **envp)
{
	t_mini	mini;
	(void)argv;
	(void)argc;
	
	g_sig = -1;
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		mini.input = readline("minishell: ");
		if (!mini.input)
		{
			mini.com_tab = NULL;
			ft_exit(&mini);
		}
		if (g_sig != -1)
		{
			if (mini.input)
				free(mini.input);
			g_sig = -1;
			continue ;
		}
		ft_copy_env2lst(&mini, envp);
		if (*mini.input)
		{
			if (input_check(mini.input))
			{
				add_history(mini.input);
				mini.com_tab = parsing(mini.input, 0 , 0);
				if (!mini.com_tab)
				{
					free_env(mini.env);
					return (0);
				}
				if (check_command(&mini) == -1)
				{
					free_com_tab(&mini);
					free_env(mini.env);
					return (0);
				}
				if (mini.com_tab)
					free_com_tab(&mini);
				if (mini.env)
					free_env(mini.env);
			}
		}
	}
	return (0);
}
