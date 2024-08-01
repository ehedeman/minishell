/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_rem_quo_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 14:40:22 by ehedeman          #+#    #+#             */
/*   Updated: 2024/07/27 10:26:57 by ehedeman         ###   ########.fr       */
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

static void	help_function(int *i, int *j, char *parsed, char *unquoted_parsed)
{
	int save;

	while (parsed[*i] && is_onstr(QUOTES, parsed[*i]))
	{
		if (check_quotes_dollar_sign(&parsed[*i]))
		{
			save = copy_quotes_dollar_sign(&unquoted_parsed[*j], &parsed[*i]);
			*i += save;
			*j += save;
		}
		else if (parsed[*i])
			*i += 1;
	}
}

int	unquoted_cpy_loop(char *parsed, char *unquoted_parsed,
	bool quotes, char quote_c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (parsed[i])
	{
		if (parsed[i] == ' ' && !quotes)
			break ;
		else if (parsed[i] == quote_c)
			break ;
		help_function(&i, &j, parsed, unquoted_parsed);
		if (!parsed[i])
			break ;
		unquoted_parsed[j] = parsed[i];
		i++;
		j++;
	}
	unquoted_parsed[j] = '\0';
	return (i);
}