/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_unquoted_cpy.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 14:35:00 by ehedeman          #+#    #+#             */
/*   Updated: 2024/08/12 09:24:08 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	help_function(t_rm_quotes *r, char *parsed, \
		char *unquoted_parsed)
{
	int	save;

	while (parsed[r->i] && is_onstr(QUOTES, parsed[r->i]))
	{
		if (check_quotes_dollar_sign(&parsed[r->i]))
		{
			save = copy_quotes_dollar_sign(&unquoted_parsed[r->j], \
				&parsed[r->i]);
			r->i += save;
			r->j += save;
		}
		else if (parsed[r->i] != r->quote_c && r->quote_c != '\0')
		{
			unquoted_parsed[r->j] = parsed[r->i];
			r->i++;
			r->j++;
		}
		else if (parsed[r->i])
		{
			r->quote_c = parsed[r->i];
			r->i += 1;
		}
	}
}

static void	unquoted_cpy_2(char *parsed, char *unquoted_parsed, \
		t_rm_quotes *r)
{
	while (parsed[r->i])
	{
		if (parsed[r->i] == ' ' && !r->quotes)
			break ;
		else if (parsed[r->i] == r->quote_c)
			break ;
		help_function(r, parsed, unquoted_parsed);
		if (!parsed[r->i])
			break ;
		unquoted_parsed[r->j] = parsed[r->i];
		r->i++;
		r->j++;
	}
	unquoted_parsed[r->j] = '\0';
}

static void	unquoted_cpy_1(char *parsed, char *unquoted_parsed, \
		t_rm_quotes *r)
{
	int	save;

	while (parsed[r->i] && (parsed[r->i] == '\'' || parsed[r->i] == '\"'))
	{
		if (r->quote_c != parsed[r->i] && r->quote_c != '\0')
		{
			if (!check_quotes_dollar_sign(&parsed[r->i]))
			{
				unquoted_parsed[r->j] = parsed[r->i];
				r->i++;
				r->j++;
			}
		}
		else
		{
			r->quote_c = parsed[r->i];
			r->quotes = !r->quotes;
		}
		if (check_quotes_dollar_sign(&parsed[r->i]))
		{
			save = copy_quotes_dollar_sign(&unquoted_parsed[r->j], \
				&parsed[r->i]);
			r->i += save;
			r->j += save;
		}
		else if (parsed[r->i] && parsed[r->i] == r->quote_c)
			r->i += 1;
	}
}

void	unquoted_cpy(char *parsed, char *unquoted_parsed, t_rm_quotes *r)
{
	while (parsed[r->i])
	{
		unquoted_cpy_1(parsed, unquoted_parsed, r);
		if (!parsed[r->i])
			break ;
		unquoted_cpy_2(parsed, unquoted_parsed, r);
		while (unquoted_parsed[r->j] != '\0')
			r->j += 1;
		r->quote_c = '\0';
		if (parsed[r->i])
			r->i += 1;
	}
	unquoted_parsed[r->j] = '\0';
}
