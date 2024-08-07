/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_get_nbr_parsed_args.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatschu <smatschu@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 13:14:35 by ehedeman          #+#    #+#             */
/*   Updated: 2024/08/07 21:49:07 by smatschu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	get_nbr_parsed_args_1(char *input, int *i, int *count, bool *quotes)
{
	*count += 1;
	while (input[*i])
	{
		if (is_onstr(OPERATORS, input[*i]) && !*quotes)
		{
			*count += 1;
			if (is_onstr(OPERATORS, input[*i + 1]))
				*i += 1;
			break ;
		}
		if (is_onstr(QUOTES, input[*i]) && input[*i] == input[*i + 1])
		{
			*count += 1;
			*i += 1;
		}
		else if (is_onstr(QUOTES, input[*i]))
			*quotes = !*quotes;
		if (is_spaces(input[*i]) && !*quotes)
			break ;
		*i += 1;
	}
}

int	get_nbr_parsed_args(char *input, int i, int count)
{
	bool	quotes;

	quotes = false;
	while (input[i])
	{
		if (is_onstr(OPERATORS, input[i]) && !quotes)
		{
			if (input[i] == input[i + 1])
				i += 2;
			count += 1;
		}
		if (is_onstr(QUOTES, input[i]))
		{
			quotes = !quotes;
			i += 1;
		}
		if (input[i] != ' ' && (!is_onstr(OPERATORS, input[i]) || quotes))
		{
			get_nbr_parsed_args_1(input, &i, &count, &quotes);
		}
		if (input[i])
			i += 1;
	}
	return (count);
}
