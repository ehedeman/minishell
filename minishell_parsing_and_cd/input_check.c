/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 14:12:00 by ehedeman          #+#    #+#             */
/*   Updated: 2024/06/13 14:21:32 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_unclosed_quotes(char *input)
{
	int	quotes_i;
	int	i;
	bool	quotes;

	quotes_i = -1;
	i = 0;
	quotes = false;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
		{
			quotes = !quotes;
			quotes_i = i;
		}
		i++;
	}
	if (quotes)
		return (1);
	return (0);
}

bool input_check(char *input)
{
    bool    valid;

    valid = true;
    if (check_unclosed_quotes(input))
    {
        write(1, UNCLOSED_QUOTES, 28);
        valid = false;
    }
    if (!valid)
        free(input);
    return (valid);
}