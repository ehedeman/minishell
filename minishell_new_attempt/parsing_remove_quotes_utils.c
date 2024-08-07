/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_remove_quotes_utils.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatschu <smatschu@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 22:10:09 by smatschu          #+#    #+#             */
/*   Updated: 2024/08/07 22:10:28 by smatschu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quotes_dollar_sign(char *parsed_at_i)
{
	if ((parsed_at_i[0] == '\'' || parsed_at_i[0] == '\"')
		&& parsed_at_i[1] == '$')
		return (1);
	return (0);
}

int	copy_quotes_dollar_sign(char *unquoted_parsed, char *parsed)
{
	int	i;

	i = 0;
	while (parsed[i])
	{
		unquoted_parsed[i] = parsed[i];
		i++;
		if (parsed[i] == '\'' || parsed[i] == '\"')
			break ;
	}
	unquoted_parsed[i] = parsed[i];
	i++;
	return (i);
}
