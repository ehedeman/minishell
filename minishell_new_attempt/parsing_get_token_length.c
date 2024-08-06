/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_get_token_length.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 13:20:02 by ehedeman          #+#    #+#             */
/*   Updated: 2024/08/06 13:32:18 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	get_token_len_1(char *input, int *i, bool *quotes, int *length)
{
	while (input[*i])
	{
		if (is_spaces(input[*i]) && !*quotes) //if there is space without it being in quotation
			break ;
		else if (is_onstr(OPERATORS, input[*i]) && !*quotes) //if theres unquoted operators
			break ;
		*length += 1;
		if (is_onstr(QUOTES, input[*i]) && input[*i + 1] == ' ') //if we have quote the word is over 100%
			break ;
		else if (is_onstr(QUOTES, input[*i]))
			*quotes = !*quotes;
		*i += 1;
	}
}

int	get_token_len(char *input)
{
	int		i;
	int		length;
	bool	quotes;

	quotes = false;
	i = 0;
	length = check_doubles(input, i);
	if (length == 1 || length == 2) //if its either double quotes or double operators
		return (length);
	while (is_spaces(input[i]))
		i += 1; //skip whitespace
	if (is_onstr(QUOTES, input[i]) == 1)
	{
		quotes = !quotes; //if there's a quote, either it completes or is a new one
		length += 1;
		i += 1;
	}
	get_token_len_1(input, &i, &quotes, &length);
	return (length);
}
