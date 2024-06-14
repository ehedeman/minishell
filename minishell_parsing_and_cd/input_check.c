/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 14:12:00 by ehedeman          #+#    #+#             */
/*   Updated: 2024/06/14 13:21:08 by ehedeman         ###   ########.fr       */
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

static int	check_missmatched_quotes(char *input)
{
	char quote_type;
	int i;
	bool quotes;

	i = 0;
	while (input[i] && !is_onstr(QUOTES, input[i]))
		i++;
	if (!input[i])
		return (0);
	quote_type = input[i];
	quotes = true;
	i++;
	while (input[i])
	{
		if (is_onstr(QUOTES, input[i]) && quotes)
		{
			if (quote_type != input[i])
				return (1);
			quotes = !quotes;
			quote_type = 0;
		}
		else if (is_onstr(QUOTES, input[i]) && !quotes)
		{
			quotes = !quotes;
			quote_type = input[i];
		}
		i++;
	}
	return (0);
}

bool input_check(char *input)
{
    bool    valid;

    valid = true;
    if (check_unclosed_quotes(input))
    {
        write(1, UNCLOSED_QUOTES, ft_strlen(UNCLOSED_QUOTES));
        valid = false;
    }
	else if (check_missmatched_quotes(input))
	{
		write(1, MISSMATCHED_QUOTES, ft_strlen(MISSMATCHED_QUOTES));
		valid = false;
	}
    if (!valid)
        free(input);
    return (valid);
}