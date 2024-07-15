/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 11:57:45 by ehedeman          #+#    #+#             */
/*   Updated: 2024/07/15 16:50:32 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parsing_error(int errnum)
{
	errnum += 1;
	return (0);
}

int	is_onstr(const char *str, int c)
{
	int	i;
	
	if (!str)
		return (-1);
	if (!c)
		return (-1);
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	get_argc(char **parsed)
{
	int	i;
	int	count;
	
	i = 0;
	count = 0;
	if (is_onstr(OPERATORS, parsed[i][0]))
		i++;
	while (parsed[i])
	{
		if (is_onstr(OPERATORS, parsed[i][0]))
			break;
		count++;
		i++;
	}
	return(count);
}

static int	remove_quotes_size(char *parsed)
{
	int	i;
	int	size;
	//char	quotes;

	i = 0;
	size = 0;
	if (!ft_strncmp(parsed, "'$PATH'", ft_strlen(parsed)))
		return (7);
	while (parsed[i])
	{
		while (parsed[i] && is_onstr(QUOTES, parsed[i]))
		{
			//quotes = parsed[i];
			i++;
		}
		while (parsed[i] && !is_onstr(QUOTES, parsed[i]))
		{
			i++;
			size++;
		}
		if (!parsed[i])
			break ;
		//quotes = 0;
	}
	return (size);
}

char *remove_quotes(char *parsed)
{
	int		i;
	int		j;
	char	quotes;
	char	*unquoted_parsed;

	i = 0;
	j = 0;
	quotes = '\0';
	unquoted_parsed = malloc((remove_quotes_size(parsed) + 1) * sizeof(char));
	if (!unquoted_parsed)
	{
		free(parsed);
		parsing_error(MALLOC_ERR);
		return (NULL);
	}
	if (!ft_strncmp(parsed, "'$PATH'", ft_strlen(parsed)))
	{
		ft_strlcpy(unquoted_parsed, parsed, 8);
		free(parsed);
		return (unquoted_parsed);
	}
	while (parsed[i])
	{
		while (parsed[i] && (parsed[i] == '\'' || parsed[i] == '\"'))
		{
			quotes = parsed[i];
			i++;
		}
		if (!parsed[i])
			break ;
		while (parsed[i] && parsed[i] != quotes)
		{
			unquoted_parsed[j] = parsed[i];
			i++;
			j++;
		}
		quotes = '\0';
	}
	unquoted_parsed[j] = '\0';
	free(parsed);
	return (unquoted_parsed);
}

t_operator	get_operator(char *operator)
{
	t_operator	op;

	if (!operator)
		op = NONE;
	else if (!ft_strncmp(operator, "|", 1))
		op = PIPE;
	else if (!ft_strncmp(operator, ">>", 2))
		op = RDR_OUT_APPEND;
	else if (!ft_strncmp(operator, ">", 1))
		op = RDR_OUT_REPLACE;
	else if (!ft_strncmp(operator, "<<", 2))
		op = RDR_INPUT_UNTIL;
	else if (!ft_strncmp(operator, "<", 1))
		op = RDR_INPUT;
	else
		op = NONE;
	return (op);
}