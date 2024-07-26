/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_remove_quotes.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 15:44:15 by ehedeman          #+#    #+#             */
/*   Updated: 2024/07/26 15:19:05 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

static void	unquoted_cpy(char *parsed, char *unquoted_parsed)
{
	char	quote_c;
	bool	quotes;
	int		save;

	quotes = false;
	quote_c = '\0';
	while (*parsed)
	{
		while (*parsed && (*parsed == '\'' || *parsed == '\"'))
		{
			quote_c = *parsed;
			quotes = !quotes;
			if (check_quotes_dollar_sign(&*parsed))
			{
				save = copy_quotes_dollar_sign(&*unquoted_parsed, &*parsed);
				parsed += save;
				unquoted_parsed += save;
			}
			else if (*parsed)
				parsed++;
		}
		if (!*parsed)
			break ;
		parsed += unquoted_cpy_loop(parsed, unquoted_parsed, quotes, quote_c);
		while (*unquoted_parsed != '\0')
			unquoted_parsed++;
		quote_c = '\0';
		if (*parsed)
			parsed++;
	}
	*unquoted_parsed = '\0';
}

static int	remove_quotes_length(char *parsed, int size, bool quotes)
{
	while (*parsed)
	{
		while (*parsed && is_onstr(QUOTES, *parsed))
		{
			quotes = !quotes;
			if (check_quotes_dollar_sign(&*parsed))
				size += 2;
			parsed++;
		}
		while (*parsed)
		{
			while (*parsed && is_onstr(QUOTES, *parsed))
			{
				quotes = !quotes;
				if (check_quotes_dollar_sign(&*parsed))
					size += 2;
				parsed++;
			}
			if (!*parsed)
				return (size);
			if (is_spaces(*parsed) && !quotes)
				return (size);
			size++;
			parsed++;
		}
		if (!*parsed)
			break ;
	}
	return (size);
}

char	*remove_quotes(char *parsed)
{
	char	*unquoted_parsed;

	unquoted_parsed = malloc(sizeof(char) * (remove_quotes_length(parsed, 0, false) + 1));
	if (!unquoted_parsed)
	{
		free(parsed);
		parsing_error(MALLOC_ERR);
		return (NULL);
	}
	unquoted_cpy(parsed, unquoted_parsed);
	free(parsed);
	return (unquoted_parsed);
}