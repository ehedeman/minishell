/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_rove_quotes_utils.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 14:40:22 by ehedeman          #+#    #+#             */
/*   Updated: 2024/08/06 14:30:24 by ehedeman         ###   ########.fr       */
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
