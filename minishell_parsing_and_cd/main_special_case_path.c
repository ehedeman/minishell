/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_special_case_path.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:28:40 by ehedeman          #+#    #+#             */
/*   Updated: 2024/07/15 17:50:02 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	remove_quotes_path(t_statement *temp, int i)
{
	char	*temp_pointer;

	temp_pointer = temp->argv[i];
	temp->argv[i] = malloc(sizeof(char) * 6);
	if (!temp->argv[i])
	{
		printf("minishell: System Error.\n");
		temp->argv[i] = temp_pointer;
		return (-1);
	}
	ft_strlcpy(temp->argv[i], "$PATH", 6);
	free(temp_pointer);
	return (0);
}

int	check_for_path_quoted(t_statement *temp)
{
	int		i;
	bool	echo_found;

	i = 0;
	if(!*temp->argv)
		return (0);
	if (!ft_strncmp(temp->argv[i], "echo", ft_strlen(temp->argv[i])))
	{
		echo_found = true;
		i++;
	}
	else
		echo_found = false;
	while (temp->argv[i])
	{
		if (!ft_strcmp(temp->argv[i], "'$PATH'") && !echo_found)
			remove_quotes_path(temp, i);
		i++;
	}
	return (0);
}