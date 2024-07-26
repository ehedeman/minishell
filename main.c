/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatschu <smatschu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/07/26 15:53:32 by smatschu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int	g_exec_file;

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
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("\0", 1);
		rl_redisplay();
	}
	else if (sig == SIGINT && g_exec_file)
		printf("\n");
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
		mini->input = readline("\033[1;31mthe minishell: \033[0m");
		if (!mini->input)
		{
			mini->com_tab = NULL;
			ft_exit(mini, "1");
		}
		if (*mini->input)
		{
			if (whitespace_check(mini->input))
				continue ;
			if (input_check(mini->input))
			{
				add_history(mini->input);
				add_to_hist_arr(&(mini->history), mini->input);
				mini->com_tab = parsing(mini->input);
				if (!mini->com_tab)
				{
					ft_env_lst_clear(mini->env, free);
					return ;
				}
				int i = 0;
				while(mini->com_tab->argv[i])
					printf("test mini->com_tab->argv[i]: %s\n", mini->com_tab->argv[i++]);
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
