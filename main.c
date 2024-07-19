/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatschu <smatschu@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 10:57:19 by ehedeman          #+#    #+#             */
/*   Updated: 2024/07/19 11:19:02 by smatschu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exec_file;
//if theres multiple output redirections it creates all of the files, then
//closes them if nessecary.
//returns only the last fd.
// (get_fd is for creating the right type of file if nessecary. else it just
//  opens the right file)

int	check_command(t_mini *mini)
{
	t_statement *temp;
	//t_mini		*testmini;
	int fd;
	//int	i;

	mini->temp = mini->com_tab;
	temp = mini->temp;
	//i = 0;
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
		write(STDOUT_FILENO, "\nminishell: ", 12);
	else if (sig == SIGINT && g_exec_file) //had issues with closing endless programs (usually you use ctrl c)
		printf("\n");					   //without else if the programm displays "minishell: " twice in that case
}										   //used global var to tell the program "hey theres smth else beign closed with ctrl c right now"
										   //so theres no need to display the new prompt cuz minishell does that anyways

int	ft_shlvl(t_mini *mini)
{
	t_env_list	*temp;
	int			num;

	temp = mini->env;
	while (temp)
	{
		if (temp == NULL)
			return (1);
		if (ft_strncmp(temp->name, "SHLVL", 5) == 0)
		{
			num = ft_atoi(temp->value);
			free(temp->value);
			num++;
			temp->value = ft_itoa(num);
			break ;
		}
		temp = temp->next;
	}
	return (0);
}

void	initialize_mini(t_mini *mini, char **envp)
{
	ft_copy_env2lst(mini, envp);
	init_history(&(mini->history));
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
	mini->com_tab = NULL;
	mini->input = NULL;
	g_exec_file = 0;
	mini->exit_status = 42; //should change this for $?, init at 0
	ft_shlvl(mini);
}

void	process_input(t_mini *mini)
{
	while (1)
	{
		mini->input = readline("the minishell: ");
		if (!mini->input)
		{
			mini->com_tab = NULL;
			ft_exit(mini);
		}
		if (*mini->input)
		{
			if (whitespace_check(mini->input))
				continue ;
			if (input_check(mini->input))
			{
				add_history(mini->input);
				add_to_hist_arr(&(mini->history), mini->input);
				mini->com_tab = parsing(mini->input, 0, 0);
				if (!mini->com_tab)
				{
					ft_env_lst_clear(mini->env, free);
					return ;
				}
				replace_env_vars(mini->com_tab->argv, mini);
				if (check_command(mini) == -1)
				{
					free_com_tab(mini);
					ft_env_lst_clear(mini->env, free);
					return ;
				}
				if (mini->com_tab)
					free_com_tab(mini);
			}
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_mini	mini;

	(void)argv;
	(void)argc;
	initialize_mini(&mini, envp);
	process_input(&mini);
	if (mini.com_tab)
		free_com_tab(&mini);
	return (0);
}
