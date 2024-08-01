/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 10:57:19 by ehedeman          #+#    #+#             */
/*   Updated: 2024/08/01 15:35:17 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int	g_sig;

void	print_statements(t_statement *statements)
{
	t_statement *current = statements;
	int i;
	while (current)
	{
		i = 0;
		printf("Statement node: %d\n", current->id);
		printf("Operator: %d\n", current->operator);
		printf("Arguments\n");
		while(i < current->argc)
		{
			printf("  argv[%d]: %s\n", i, current->argv[i]);
			i++;	
		}
		current = current->next;
		printf("\n");
	}
}

//we can delete this later, i was getting lost when testing in different shlvls
char	*ft_prompt()
{
	char	*shlvl;
	char	*prompt;
	char	*current;

	shlvl = getenv("SHLVL");
	prompt = ft_strjoin("\033[1;31m", "minishell shlvl ");
	current = prompt;
	prompt = ft_strjoin(prompt, shlvl);
	free(current);
	current = prompt;
	prompt = ft_strjoin(prompt, ": \033[0m");
	free(current);
	return (prompt);
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
	t_env_list	*current;
	int			num;

	current = mini->env;
	while (current)
	{
		if (current == NULL)
			return (1);
		if (ft_strncmp(current->name, "SHLVL", 5) == 0)
		{
			num = ft_atoi(current->value);
			free(current->value);
			num++;
			current->value = ft_itoa(num);
			break ;
		}
		current = current->next;
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
			if(!g_sig)
				ft_exit(mini, "0");
			ft_exit(mini, "255");
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
				replace_env_vars(mini->com_tab->argv, mini);
			
				//for testing
			//	print_statements(mini->com_tab);
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
