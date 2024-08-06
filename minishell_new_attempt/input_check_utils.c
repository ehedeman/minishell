/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 14:57:12 by ehedeman          #+#    #+#             */
/*   Updated: 2024/08/06 14:58:49 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_incomplete_out_red_1(char *input, int *i, int *redirect)
{
	while (input[*i] == '>' && input[*i])
	{
		*redirect += 1;
		*i += 1;
		if (*redirect > 2)
			return (1);
	}
	return (0);
}

int	check_missmatched_quotes_1(char *input, char *quote_type, int *i, \
	bool *quotes)
{
	while (input[*i])
	{
		if (is_onstr(QUOTES, input[*i]) && *quotes)
		{
			if (*quote_type != input[*i])
				return (1);
			*quotes = !*quotes;
			*quote_type = 0;
		}
		else if (is_onstr(QUOTES, input[*i]) && !*quotes)
		{
			*quotes = !*quotes;
			*quote_type = input[*i];
		}
		*i += 1;
	}
	return (0);
}
