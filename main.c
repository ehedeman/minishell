/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 10:57:19 by ehedeman          #+#    #+#             */
/*   Updated: 2024/07/30 12:14:11 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int	g_sig;

//we can delete this later, i was getting lost when testing in different shlvls
char	*ft_prompt()
{
	char	*shlvl;
	char	*prompt;
	char	*temp;

	shlvl = getenv("SHLVL");
	prompt = ft_strjoin("\033[1;31m", "minishell shlvl ");
	temp = prompt;
	prompt = ft_strjoin(prompt, shlvl);
	free(temp);
	temp = prompt;
	prompt = ft_strjoin(prompt, ": \033[0m");
	free(temp);
	return (prompt);
}

int	check_command(t_mini *mini)
{
	t_statement *temp;

	mini->temp = mini->com_tab;
	temp = mini->temp;
	if (check_command_after_file_rdr(temp))
		temp = command_after_file_rdr(temp, mini);
	check_commands_loop(temp, mini, 0);
	// printf("\n\nLIST BEFORE RETURNING FROM CHECK_COM:\n");
	// ft_print_env_lst(mini->env);
	return (0);
}

void	handler(int sig)
{
	if (sig == SIGINT && !g_sig)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("\0", 1);
		rl_redisplay();
	}
	else if (sig == SIGINT && g_sig)
		printf("\n");
	else if (sig == SIGQUIT && !g_sig)
		rl_replace_line("\0", 1);
	else if (sig == SIGQUIT)
		printf("Quit (core dumped)\n");
}

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
	signal(SIGQUIT, handler);
	mini->com_tab = NULL;
	mini->input = NULL;
	g_sig = 0;
	mini->exit_status = 0;
	ft_shlvl(mini);
}

void	process_input(t_mini *mini)
{
	while (1)
	{
		//just for testing with different shlvls, can go back to the simple one later
		char	*prompt;
		prompt = ft_prompt();
		mini->input = readline(prompt);
		free(prompt);
		//mini->input = readline("\033[1;31mthe minishell: \033[0m");
		if (!mini->input)
		{
			mini->com_tab = NULL;
			ft_exit(mini, "1");
		}
		if (*mini->input)
		{
			if (whitespace_check(mini)) //frees input if nessecary
				continue ;
			if (input_check(mini->input))
			{
				add_history(mini->input);
				add_to_hist_arr(&(mini->history), mini->input);
				mini->com_tab = parsing(mini->input);
				if (!mini->com_tab)
				{
					ft_env_lst_clear(mini->env, free);
					free(mini->input);
					return ;
				}
				// //for testing
				// int i = -1;
				// while(mini->com_tab->argv[++i])
				// 	printf("test mini->com_tab->argv[%d]: %s\n",i, mini->com_tab->argv[i]);
				replace_env_vars(mini->com_tab->argv, mini);

				// //testing after expansion
				// i = -1;
				// while(mini->com_tab->argv[++i])
				// 	printf("after expanstion mini->com_tab->argv[%d]: %s\n", i, mini->com_tab->argv[i]);
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
		if (mini->input)
		{
			free(mini->input);
			mini->input = NULL;
		}
	}
}

int	main(int argc, char **argv, char **envp)	
{
	t_mini	mini;
	int i;

	i = 0;
	(void)argv;
	(void)argc;
	if (argc == 2)
		while (i++ < 6)
			printf("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n");
	initialize_mini(&mini, envp);
	process_input(&mini);
	if (mini.com_tab)
		free_com_tab(&mini);
	return (0);
}
