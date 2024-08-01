/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_set_output_file.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 15:03:25 by ehedeman          #+#    #+#             */
/*   Updated: 2024/08/01 15:39:37 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_temp_output_as_stdout(t_mini *mini)
{
	mode_t	mode;

	mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	mini->temp_output = open(".output", O_RDWR | O_CREAT | O_TRUNC, mode);
	if (mini->temp_output < 0)
	{
		printf("minishell: system error.");
		return (-1);
	}
	redirect_stdout(mini, mini->temp_output); //output file is now the stdout
	return (0);
}

int	set_temp_output_as_stdin(t_mini *mini)
{
	mini->temp_output = open(".output", O_RDWR);
	if (mini->temp_output < 0)
	{
		printf("minishell: system error.");
		return (-1);
	}
	redirect_stdin(mini, mini->temp_output); //output file is now the stdout
	return (0);
}
