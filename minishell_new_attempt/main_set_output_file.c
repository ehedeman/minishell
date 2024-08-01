/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_set_output_file.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 15:03:25 by ehedeman          #+#    #+#             */
/*   Updated: 2024/08/01 15:04:34 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_temp_output_as_stdout(t_statement *mini)
{
	mode_t	mode;

	mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	mini->output = open(".output", O_RDWR | O_CREAT | O_TRUNC, mode);
	if (mini->output < 0)
	{
		printf("minishell: system error.");
		return (-1);
	}
	redirect_stdout(mini, mini->output); //output file is now the stdout
	return (0);
}

void	set_temp_output_as_stdin(t_statement *mini)
{
	mini->output = open(".output", O_RDWR);
	if (mini->output < 0)
	{
		printf("minishell: system error.");
		return (-1);
	}
	redirect_stdin(mini, mini->output); //output file is now the stdout
	return (0);
}
