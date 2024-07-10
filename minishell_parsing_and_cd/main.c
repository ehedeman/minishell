/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatschu <smatschu@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 10:57:19 by ehedeman          #+#    #+#             */
/*   Updated: 2024/07/10 11:50:45 by smatschu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_exec_file;
//if theres multiple output redirections it creates all of the files, then
//closes them if nessecary.
//returns only the last fd.
// (get_fd is for creating the right type of file if nessecary. else it just
//  opens the right file)
//test github
int	check_redirect(t_mini *mini)
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
				return (fd);
		}
		else if (mini->temp->operator == RDR_INPUT ||
			mini->temp->operator == RDR_INPUT_UNTIL)
		{
			if (mini->temp->next->operator != RDR_INPUT_UNTIL &&
				mini->temp->next->operator != RDR_INPUT)
			{
				redirect_input(mini->temp);
				return (1);
			}
		}
		else if (mini->temp->operator == PIPE || mini->temp->operator == NONE)
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
	//t_mini		*testmini;
	int fd;
	int	i;

	mini->temp = mini->com_tab;
	temp = mini->temp;
	while (temp)
	{
		i = 0;
		fd = check_redirect(mini); //standart is 1, if its got redirection then its set new
		while (i < temp->argc && *temp->argv)
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
			else if (ft_strncmp(temp->argv[i], "export", 6) == 0)
			{
				//return(ft_export(mini));
				ft_export(mini);
				// printf("LIST AFTER EXPORT:\n");
				// ft_print_env_lst(mini->env);
				return (0);
			}
			else if (temp->operator != SKIP)
			{
				if (exec_command(temp) == -1)
					return (-1);
				return (0);
			}
			i++;
		}
		temp = mini->temp;
		if (fd != 1 && fd != 2)
			close(fd);
		temp = temp->next;
	}
	// printf("\n\nLIST BEFORE RETURNING FROM CHECK_COM:\n");
	// ft_print_env_lst(mini->env);
	return (0);
}

void	handler(int sig)
{
	if (sig == SIGINT && !g_exec_file)
		printf("\nminishell: ");
	else if (sig == SIGINT && g_exec_file) //had issues with closing endless programs (usually you use ctrl c)
		printf("\n");					   //without else if the programm displays "minishell: " twice in that case
}										   //used global var to tell the program "hey theres smth else beign closed with ctrl c right now"
										   //so theres no need to display the new prompt cuz minishell does that anyways

int main (int argc, char **argv, char **envp)
{
	t_mini	mini;
	(void)argv;
	(void)argc;

	ft_copy_env2lst(&mini, envp); //took out of the while(1) so it doesnt reset at every readline
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
	mini.com_tab = NULL;
	mini.input = NULL;
	g_exec_file = 0;
	
	while (1)
	{
		mini.input = readline("minishell: ");

		if (!mini.input)
		{
			mini.com_tab = NULL;
			//mini.env = NULL;
			ft_exit(&mini);
		}
		if (*mini.input)
		{
			if (input_check(mini.input))
			{
				add_history(mini.input);
				mini.com_tab = parsing(mini.input, 0 , 0);
				if (!mini.com_tab)
				{
					//ft_env_lst_clear(mini.env, free);
					return (0);
				}
				if (check_command(&mini) == -1)
				{
					free_com_tab(&mini);
					//ft_env_lst_clear(mini.env, free);
					return (0);
				}
				if (mini.com_tab)
					free_com_tab(&mini);
			}
		}
		//ft_env_lst_clear(mini.env, free);
	}
	return (0);
}
