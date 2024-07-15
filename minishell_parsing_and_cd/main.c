/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 10:57:19 by ehedeman          #+#    #+#             */
/*   Updated: 2024/07/15 15:41:57 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_exec_file;
//if theres multiple output redirections it creates all of the files, then
//closes them if nessecary.
//returns only the last fd.
// (get_fd is for creating the right type of file if nessecary. else it just
//  opens the right file)


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
	i = 0;
	fd = 0;
	if (check_command_after_file_rdr(temp))
		temp = command_after_file_rdr(temp, mini);
	check_commands_loop(temp, mini, fd, 0);
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
					ft_env_lst_clear(mini.env, free);
					return (0);
				}
				replace_env_vars(mini.com_tab->argv);
				if (check_command(&mini) == -1)
				{
					free_com_tab(&mini);
					ft_env_lst_clear(mini.env, free);
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
