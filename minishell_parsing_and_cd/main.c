/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 10:57:19 by ehedeman          #+#    #+#             */
/*   Updated: 2024/06/14 13:53:21 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main_error(int errnum)
{
	if (errnum == MALLOC_ERR)
		write(2, FAILED_MALLOC, ft_strlen(FAILED_MALLOC));
	if (errnum == SYNTAX_ERR)
		write(2, UNEXPECTED_TOKEN, ft_strlen(UNEXPECTED_TOKEN));
	if (errnum == PATH_ERR)
		write(2, FAILED_PATH, ft_strlen(FAILED_PATH));
	return (-1);
}

//to check the input/if everything was parsed correctly
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
			// printf("%i\n", temp->operator);
			// printf("%i\n", temp->argc);
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
			if (ft_strncmp(temp->argv[i], "cd", 2) == 0)
				ft_cd(temp, i);
			else if (ft_strncmp(temp->argv[i], "pwd", 3) == 0)
				ft_pwd(check_redirect(temp));
			else if (ft_strncmp(temp->argv[i], "exit", 5) == 0)
				ft_exit(mini);
			else if (ft_strnstr(temp->argv[i], "print", 5))
			{
				ft_print(mini);
				if (temp->operator == NONE)
					return ;
			}
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
