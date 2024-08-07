/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 10:57:19 by ehedeman          #+#    #+#             */
/*   Updated: 2024/08/07 12:48:05 by ehedeman         ###   ########.fr       */
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
		// printf("Arguments\n");
		// while(i < current->argc)
		// {
		// 	printf("  argv[%d]: %s\n", i, current->argv[i]);
		// 	i++;	
		// }
		current = current->next;
		printf("\n");
	}
}

int	process_input_one(t_mini *mini)
{
	if (whitespace_check(mini)) //frees input if nessecary
		return (-1); // = continue ;
	if (input_check(mini->input))
	{
		add_history(mini->input);
		add_to_hist_arr(&(mini->history), mini->input);
		mini->com_tab = parsing(mini->input);
		if (!mini->com_tab)
		{
			ft_env_lst_clear(mini->env, free);
			free(mini->input);
			return (1); // = return ;
		}
		replace_env_vars(mini->com_tab->argv, mini);
		if (execution(mini) == -1)
		{
			free_com_tab(mini);
			ft_env_lst_clear(mini->env, free);
			return (1);
		}
		if (mini->com_tab)
			free_com_tab(mini);
	}
	return (0);
}

//char *prompt;
// prompt = ft_prompt();
// mini->input = readline(prompt);
// free(prompt);
void	process_input(t_mini *mini, int return_value)
{
	while (1)
	{
		mini->input = readline("\033[1;31mthe minishell: \033[0m");
		if (!mini->input)
		{
			mini->com_tab = NULL;
			if (!g_sig)
				ft_exit(mini, "0");
			ft_exit(mini, "255");
		}
		if (*mini->input)
		{
			return_value = process_input_one(mini);
			if (return_value == 1)
				return ;
			else if (return_value == -1)
				continue ;
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
	int		i;

	i = 0;
	(void)argv;
	(void)argc;
	if (argc == 2)
		while (i++ < 6)
			printf("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n");
	initialize_mini(&mini, envp);
	process_input(&mini, 0);
	if (mini.com_tab)
		free_com_tab(&mini);
	return (0);
}


//we can delete this later, i was getting lost when testing in different shlvls
// char	*ft_prompt(void)
// {
// 	char	*shlvl;
// 	char	*prompt;
// 	char	*current;

// 	shlvl = getenv("SHLVL");
// 	prompt = ft_strjoin("\033[1;31m", "minishell shlvl ");
// 	current = prompt;
// 	prompt = ft_strjoin(prompt, shlvl);
// 	free(current);
// 	current = prompt;
// 	prompt = ft_strjoin(prompt, ": \033[0m");
// 	free(current);
// 	return (prompt);
// }