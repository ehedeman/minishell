/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 10:57:19 by ehedeman          #+#    #+#             */
/*   Updated: 2024/06/13 14:21:25 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


 //set everything that needs to be malloced to zero later so there
 //can be one function thats like "is this zero? no? then free it."
static int	set_values(t_mini *mini)
{
	mini->fd = 1;
	// mini->mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	// mini->builtins_tab = malloc(sizeof(char *) * 7);
	// if (!mini->builtins_tab)
	// 	return (1);
	// mini->builtins_tab[6] = NULL;
	// fill_builtins_tab(mini->builtins_tab);
	return (0);
}

void	ft_print(t_mini *mini)
{
	int i;
	t_statement *temp;

	temp = mini->com_tab;
	while (temp)
	{
		i = 0;
		while (temp->argv[i])
		{
			printf("%s\n", temp->argv[i]);
			printf("%i\n", temp->operator);
			printf("%i\n", temp->argc);
			i++;
		}
		temp = temp->next;
	}
}

void	check_command(t_mini *mini)
{
	t_statement *temp;
	int	i;

	temp = mini->com_tab;
	while (temp)
	{
		i = 0;
		while (temp->argv[i])
		{
			printf("%s\n", temp->argv[i]);
			if (ft_strncmp(temp->argv[i], "cd", 2) == 0)
				ft_cd(temp, i);
			else if (ft_strncmp(temp->argv[i], "pwd", 3) == 0)
				ft_pwd(mini);
			else if (ft_strncmp(temp->argv[i], "exit", 5) == 0)
				ft_exit(mini);
			else if (ft_strnstr(temp->argv[i], "print", 5))
				ft_print(mini);
			else 
			{
				write(1, "Command not found.\n", 19);
				return ;
			}
			i++;
		}
		temp = temp->next;
	}
}

int	main(void)
{
	t_mini	mini;
	set_values(&mini);
	while (1)
	{
		mini.input = readline("minishell: ");
		if (!mini.input)
		{
			write(2, "Error\n", 6);
			return (0);
		}
		if (*mini.input)
		{
			if (input_check(mini.input))
			{
				add_history(mini.input);
				mini.com_tab = parsing(mini.input, 0 , 0);
				if (!mini.com_tab)
					return (0);
				check_command(&mini);
				if (mini.com_tab)
					free_com_tab(&mini);
			}
		}
	}
	return (0);
}
