/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:11:09 by ehedeman          #+#    #+#             */
/*   Updated: 2024/07/16 17:26:12 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_history(void)
{
	HIST_ENTRY **history_list;
	int	i;

	i = 0;

	while (history_list[i])
	{
		printf("%s\n", history_list[i]);
		i++;
	}
}