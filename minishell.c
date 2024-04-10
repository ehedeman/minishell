/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 12:16:09 by ehedeman          #+#    #+#             */
/*   Updated: 2024/04/10 13:20:28 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_values(t_mini *mini)
{
	mini->bool_redirect = 0;
}

int main(void)
{
	t_mini	mini;

	set_values(&mini);
	while (1)
	{
		mini.input = readline("Minishell: ");
		if (!mini.input)
		{
			write(2, "Error\n", 6);
			return (0);
		}
		if (*mini.input)
		{
			add_history(mini.input);
			if (ft_strnstr(mini.input, "ls", ft_strlen(mini.input)))
				ft_ls();
			else if (ft_strncmp(mini.input, "pwd", ft_strlen(mini.input)) == 0)
				ft_pwd();
			else if (ft_strnstr(mini.input, "cd", ft_strlen(mini.input)))
				ft_cd(mini.input);
			else if (ft_strncmp(mini.input, "red", ft_strlen(mini.input)) == 0)
				redirect("testfile.txt", "Hello how ur doin?", 3);
		}
		free(mini.input);
	}
	return (0);
}