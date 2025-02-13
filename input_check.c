/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 14:12:00 by ehedeman          #+#    #+#             */
/*   Updated: 2024/08/12 09:10:41 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_unclosed_quotes(char *input)
{
	int		i;
	bool	quotes;

	i = 0;
	quotes = false;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
		{
			quotes = !quotes;
		}
		i++;
	}
	if (quotes)
		return (1);
	return (0);
}

// static int	check_missmatched_quotes(char *input)
// {
// 	char	quote_type;
// 	int		i;
// 	bool	quotes;

// 	i = 0;
// 	while (input[i] && !is_onstr(QUOTES, input[i]))
// 		i++;
// 	if (!input[i])
// 		return (0);
// 	quote_type = input[i];
// 	quotes = true;
// 	i++;
// 	if (check_missmatched_quotes_1(input, &quote_type, &i, &quotes))
// 		return (1);
// 	return (0);
// }

static int	check_incomplete_out_red(char *input, int i)
{
	int	redirect;

	redirect = 0;
	while (input[i])
	{
		while (input[i] != '>' && input[i])
			i++;
		if (check_incomplete_out_red_1(input, &i, &redirect))
			return (1);
		while (is_spaces(input[i]) && input[i])
			i++;
		if (is_onstr(OPERATORS, input[i]) && redirect)
			return (1);
		else if (!input[i] && redirect)
			return (1);
		else if (!input[i])
			break ;
		else if (redirect && !is_onstr(OPERATORS, input[i]))
			redirect = 0;
		i++;
	}
	return (0);
}

bool	input_check(char *input)
{
	bool	valid;

	valid = true;
	if (check_unclosed_quotes(input))
	{
		write(1, UNCLOSED_QUOTES, ft_strlen(UNCLOSED_QUOTES));
		valid = false;
	}
	// else if (check_missmatched_quotes(input))
	// {
	// 	write(1, MISSMATCHED_QUOTES, ft_strlen(MISSMATCHED_QUOTES));
	// 	valid = false;
	// }
	else if (check_incomplete_out_red(input, 0))
	{
		write(1, UNFINI_OUT_RED, ft_strlen(UNFINI_OUT_RED));
		valid = false;
	}
	if (valid)
		valid = input_check_two(input, valid);
	if (!valid)
		add_history(input);
	return (valid);
}
