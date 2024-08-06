/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 13:06:34 by ehedeman          #+#    #+#             */
/*   Updated: 2024/08/06 13:31:43 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	copy_input_to_parsed(char *input, char **parsed, int i, int j)
{
	int		k; //variable for character-pointers of parsed
	int		length;
	bool	quotes;

	k = 0;
	quotes = false;
	length = get_token_len(&input[i]);
	while (input[i] && k < length)
	{
		if (is_onstr(QUOTES, input[i])) //just nessecary to know if space needs to be copied
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

static int	fill_array(char *input, char **parsed, int nbr_args) //loop from parsing input
{
	int	i; //variable for input-pointers
	int	j; //variable for word-pointers
	int	length; //variable for getting the word length needed for parsed[j]

	i = 0;
	j = 0;
	while (input[i] && j < nbr_args) // if j = nbr_args then it needs to be NULL | to avoid segfault
	{
		length = get_token_len(&input[i]);
		if (length == 0)
		{
			i++;
			continue ;
		}
		parsed[j] = malloc(sizeof(char) * (length + 1)); //allocating the length-of-word space
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

	nbr_args = get_nbr_parsed_args(input, 0, 0) + 1; //plus one to terminate
	parsed = malloc(sizeof(char *) * nbr_args);
	// parsed = ft_split(input, ' ');
	if (!parsed)
	{
		free(input);
		parsing_error(MALLOC_ERR);
		return (NULL);
	}
	if (fill_array(input, parsed, nbr_args))
		return (NULL);
	return (parsed);
}
