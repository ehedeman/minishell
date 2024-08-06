/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_get_nbr_parsed_args.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 13:14:35 by ehedeman          #+#    #+#             */
/*   Updated: 2024/08/06 13:37:26 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	get_nbr_parsed_args_1(char *input, int *i, int *count, bool *quotes)
{
	*count += 1;
	while (input[*i])
	{
		if (is_onstr(OPERATORS, input[*i]) && !*quotes) //if unquoted operator then start again
		{
			*count += 1;
			if (is_onstr(OPERATORS, input[*i + 1]))
				*i += 1;
			break ;
		}
		if (is_onstr(QUOTES, input[*i]) && input[*i] == input[*i + 1]) //doublequotes r supposed to get their own args
		{
			*count += 1;
			*i += 1;
		}
		else if (is_onstr(QUOTES, input[*i]))
			*quotes = !*quotes;
		if (is_spaces(input[*i]) && !*quotes) //if we have a space w/o quotes then the next could be a operator
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
				i += 2; //skip to symbol after operators
			count += 1;
		} //again with the operators, fixed length cuz easier
		if (is_onstr(QUOTES, input[i])) //note quotes but no new statement
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
