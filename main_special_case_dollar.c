/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_special_case_path.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:28:40 by ehedeman          #+#    #+#             */
/*   Updated: 2024/07/15 19:03:04 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	remove_quotes_main(t_statement *temp, int i)
{
	char	*temp_pointer;
	char	buff[4000];

	temp_pointer = temp->argv[i];
	temp->argv[i] = malloc(sizeof(char) * ft_strlen(temp->argv[i]) - 1);
	if (!temp->argv[i])
	{
		printf("minishell: System Error.\n");
		temp->argv[i] = temp_pointer;
		return (-1);
	}
	ft_strlcpy(buff, &temp_pointer[1], ft_strlen(temp->argv[i]));
	ft_strlcpy(temp->argv[i], buff, ft_strlen(temp->argv[i]));
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
		if (!ft_strncmp(temp->argv[i], "'$", 2) && !echo_found)
			remove_quotes_main(temp, i);
		i++;
	}
	return (0);
}