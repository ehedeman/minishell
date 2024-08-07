/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_set_output_file.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatschu <smatschu@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 15:03:25 by ehedeman          #+#    #+#             */
/*   Updated: 2024/08/07 21:47:51 by smatschu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_temp_output_as_stdout(t_mini *mini, int reset)
{
	mode_t	mode;

	mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	mini->temp_output = open(mini->out_path, O_RDWR | O_CREAT | O_TRUNC, mode);
	if (mini->temp_output < 0)
	{
		printf("minishell: system error.");
		return (-1);
	}
	redirect_stdout(mini, mini->temp_output, reset);
	return (0);
}

int	set_temp_output_as_stdin(t_mini *mini)
{
	mini->temp_output = open(mini->out_path, O_RDWR);
	if (mini->temp_output < 0)
	{
		printf("minishell: system error.");
		return (-1);
	}
	redirect_stdin(mini, mini->temp_output, 0);
	return (0);
}
