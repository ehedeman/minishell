/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_arg_to_argv_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 16:03:44 by ehedeman          #+#    #+#             */
/*   Updated: 2024/08/11 16:13:45 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	copy_flags(t_statement *temp, t_mini *mini, int *i, int *j)
{
	if (!ft_strncmp(mini->additional_args[0], "-", 1))
	{
		temp->argv[1] = malloc(sizeof(char) * \
			ft_strlen(mini->additional_args[0]) + 1);
		if (!temp->argv[1])
			return (1);
		ft_strlcpy(temp->argv[1], mini->additional_args[0], \
			ft_strlen(mini->additional_args[0]) + 1);
		*i += 1;
		*j = 1;
	}
	return (0);
}
