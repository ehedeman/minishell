/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_rove_quotes.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 15:44:15 by ehedeman          #+#    #+#             */
/*   Updated: 2024/08/06 14:31:20 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	remove_quotes_length_1(char *parsed, t_rm_quotes *r)
{
	while (parsed[r->i])
	{
		while (parsed[r->i] && is_onstr(QUOTES, parsed[r->i]))
		{
			if (r->quote_c != parsed[r->i] && r->quote_c != '\0')
			{
				r->size++;
				r->i++;
			}
			else
			{
				r->quotes = !r->quotes;
				r->quote_c = parsed[r->i];
				r->i += 1;
			}
			if (check_quotes_dollar_sign(&parsed[r->i]))
				r->size += 2;
		}
		if (!parsed[r->i])
			return (1);
		if (is_spaces(parsed[r->i]) && !r->quotes)
			return (1);
		r->size += 1;
		r->i += 1;
	}
	return (0);
}

static int	rm_quotes_len(char *parsed, t_rm_quotes *r)
{
	while (parsed[r->i])
	{
		while (parsed[r->i] && is_onstr(QUOTES, parsed[r->i]))
		{
			if (r->quote_c != parsed[r->i] && r->quote_c != '\0')
			{
				r->size++;
				r->i++;
			}
			else
			{
				r->quotes = !r->quotes;
				r->quote_c = parsed[r->i];
				r->i += 1;
			}
			if (check_quotes_dollar_sign(&parsed[r->i]))
				r->size += 2;
		}
		if (remove_quotes_length_1(parsed, r))
			return (r->size);
		if (!parsed[r->i])
			break ;
	}
	return (r->size);
}

static t_rm_quotes	*init_struct(void)
{
	t_rm_quotes	*new;

	new = malloc(sizeof(t_rm_quotes) * 1);
	if (!new)
		return (NULL);
	new->size = 0;
	new->i = 0;
	new->j = 0;
	new->quotes = false;
	new->quote_c = '\0';
	return (new);
}

char	*remove_quotes(char *parsed)
{
	char			*unquoted_pars;
	t_rm_quotes		*r;

	r = init_struct();
	if (!r)
	{
		free(parsed);
		parsing_error(MALLOC_ERR);
		return (NULL);
	}
	unquoted_pars = malloc(sizeof(char) * (rm_quotes_len(parsed, r) + 1));
	if (!unquoted_pars)
	{
		free(parsed);
		parsing_error(MALLOC_ERR);
		return (NULL);
	}
	r->i = 0;
	unquoted_cpy(parsed, unquoted_pars, r);
	free(r);
	free(parsed);
	return (unquoted_pars);
}
