/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_remove_quotes.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 15:44:15 by ehedeman          #+#    #+#             */
/*   Updated: 2024/07/24 16:42:16 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

static void	unquoted_cpy(char *parsed, char *unquoted_parsed, int i, int j)
{
	char	quote_c;
	bool	quotes;

	quotes = false;
	quote_c = '\0';
	while (parsed[i])
	{
		while (parsed[i] && (parsed[i] == '\'' || parsed[i] == '\"'))
		{
			quote_c = parsed[i];
			quotes = !quotes;
			i++;
		}
		if (!parsed[i])
			break ;
		while (parsed[i])
		{
			if (parsed[i] == ' ' && !quotes)
				break ;
			else if (parsed[i] == quote_c)
				break ;
			while (parsed[i] && is_onstr(QUOTES, parsed[i]))
				i++;
			if (!parsed[i])
				return ;
			unquoted_parsed[j] = parsed[i];
			i++;
			j++;
		}
		quote_c = '\0';
		if (parsed[i])
			i++;
	}
	unquoted_parsed[j] = '\0';
}

static int	remove_quotes_length(char *parsed)
{
	int	i;
	int	size;
	bool quotes;

	i = 0;
	size = 0;
	quotes = false;
	if (!ft_strncmp(parsed, "\'$", 2))
		return (ft_strlen(parsed));
	while (parsed[i])
	{
		while (parsed[i] && is_onstr(QUOTES, parsed[i]))
		{
			quotes = !quotes;
			i++;
		}
		while (parsed[i])
		{
			while (parsed[i] && is_onstr(QUOTES, parsed[i]))
				i++;
			if (!parsed[i])
				return (size);
			if (is_spaces(parsed[i]) && !quotes)
				return (size);
			size++;
			i++;
		}
		if (!parsed[i])
			break ;
	}
	return (size);
}

char	*remove_quotes(char *parsed)
{
	char	*unquoted_parsed;

	unquoted_parsed = malloc(sizeof(char) * (remove_quotes_length(parsed) + 1));
	if (!unquoted_parsed)
	{
		free(parsed);
		parsing_error(MALLOC_ERR);
		return (NULL);
	}
	if (!ft_strncmp(parsed, "\'$", 2))
	{
		ft_strlcpy(unquoted_parsed, parsed, ft_strlen(parsed) + 1);
		free(parsed);
		return (unquoted_parsed);
	}
	unquoted_cpy(parsed, unquoted_parsed, 0 , 0);
	free(parsed);
	return (unquoted_parsed);
}