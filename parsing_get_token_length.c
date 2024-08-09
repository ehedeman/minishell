/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_get_token_length.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatschu <smatschu@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 13:20:02 by ehedeman          #+#    #+#             */
/*   Updated: 2024/08/07 21:50:25 by smatschu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	get_token_len_1(char *input, int *i, bool *quotes, int *length)
{
	while (input[*i])
	{
		if (is_spaces(input[*i]) && !*quotes)
			break ;
		else if (is_onstr(OPERATORS, input[*i]) && !*quotes)
			break ;
		*length += 1;
		if (is_onstr(QUOTES, input[*i]) && input[*i + 1] == ' ')
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
	if (length == 1 || length == 2)
		return (length);
	while (is_spaces(input[i]))
		i += 1;
	if (is_onstr(QUOTES, input[i]) == 1)
	{
		quotes = !quotes;
		length += 1;
		i += 1;
	}
	get_token_len_1(input, &i, &quotes, &length);
	return (length);
}
