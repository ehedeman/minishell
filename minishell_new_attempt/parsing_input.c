/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatschu <smatschu@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 13:06:34 by ehedeman          #+#    #+#             */
/*   Updated: 2024/08/07 21:51:37 by smatschu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	copy_input_to_parsed(char *input, char **parsed, int i, int j)
{
	int		k;
	int		length;
	bool	quotes;

	k = 0;
	quotes = false;
	length = get_token_len(&input[i]);
	while (input[i] && k < length)
	{
		if (is_onstr(QUOTES, input[i]))
			quotes = !quotes;
		if (is_spaces(input[i]) && !quotes)
			i++;
		else
		{
			parsed[j][k] = input[i];
			i++;
			k++;
		}
	}
	parsed[j][k] = '\0';
	return (i);
}

static int	fill_array(char *input, char **parsed, int nbr_args, int i)
{
	int	j;
	int	length;

	j = 0;
	while (input[i] && j < nbr_args)
	{
		length = get_token_len(&input[i]);
		if (length == 0)
		{
			i++;
			continue ;
		}
		parsed[j] = malloc(sizeof(char) * (length + 1));
		if (!parsed[j])
		{
			free(parsed);
			free(input);
			parsing_error(MALLOC_ERR);
			return (1);
		}
		i = copy_input_to_parsed(input, parsed, i, j);
		j++;
	}
	parsed[j] = NULL;
	return (0);
}

char	**parsing_input(char *input)
{
	char	**parsed;
	int		nbr_args;

	nbr_args = get_nbr_parsed_args(input, 0, 0) + 1;
	parsed = malloc(sizeof(char *) * nbr_args);
	if (!parsed)
	{
		free(input);
		parsing_error(MALLOC_ERR);
		return (NULL);
	}
	if (fill_array(input, parsed, nbr_args, 0))
		return (NULL);
	return (parsed);
}
