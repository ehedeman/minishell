/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 13:10:38 by ehedeman          #+#    #+#             */
/*   Updated: 2024/07/24 16:42:31 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_token_len(char *input)
{
	int i;
	int length;
	bool quotes;

	quotes = false;
	i = 0;
	length = check_doubles(input, i);
	if (length == 1 || length == 2) //if its either double quotes or double operators
		return (length);
	while (is_spaces(input[i]))
		i++; //skip whitespace
	if(is_onstr(QUOTES, input[i]) == 1)
	{
		quotes = !quotes; //if there's a quote, either it completes or is a new one
		length++;
		i++;
	}
	while (input[i])
	{
		if (is_spaces(input[i]) && !quotes) //if there is space without it being in quotation
			break ;
		else if (is_onstr(OPERATORS, input[i]) && !quotes)//if theres unquoted operators
			break ;
		length++;
		if (is_onstr(QUOTES, input[i])) //if we have quote the word is over 100%
			break ;
		i++;
	}
	return (length);
}

static int	get_nbr_parsed_args(char *input, int i, int count)
{
	bool	quotes;

	quotes = false;
	while (input[i])
	{
		if (is_onstr(OPERATORS, input[i]) && !quotes)
		{
			if (is_onstr(OPERATORS, input[i + 1]))
				i += 2; //skip to symbol after operators
			count++;
		} //again with the operators, fixed length cuz easier
		if (is_onstr(QUOTES, input[i])) //note quotes but no new statement
			quotes = !quotes; 
		if (input[i] != ' ' && !is_onstr(OPERATORS, input[i]))
		{
			count++;
			while (input[i])
			{
				if (is_onstr(OPERATORS, input[i]) && !quotes) //if unquoted operator then start again
					break ;
				if (is_onstr(QUOTES, input[i]) && input[i] == input[i + 1]) //doublequotes r supposed to get their own argv
					count++;
				else if (is_onstr(QUOTES, input[i]))
					quotes = !quotes;
				if (is_spaces(input[i]) && !quotes) //if we have a space w/o quotes then the next could be a operator
					break ;
				i++;
			}
		}
		if (input[i])
			i++;
	}
	return (count);
}

static int	copy_input_to_parsed(char *input, char **parsed, int i, int j)
{
	int	k; //variable for character-pointers of parsed
	int	length;
	bool quotes;

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

static int	make_statement_list(t_statement *temp, char **parsed, int i) //i = variable for word pointers
{
	int	j; //variable for temp-argv-pointer

	while (parsed[i])
	{
		j = 0;
		while (parsed[i] && !is_onstr(OPERATORS, parsed[i][0]))
		{
			temp->argv[j] = remove_quotes(parsed[i]);
			if (temp->argv[j] == NULL)
				return (1);
			i++;
			j++;
		}
		temp->argv[j] = NULL;
		if (!parsed[i])
			break ;
		temp->operator = get_operator(parsed[i]);
		temp->next = p_new_node(get_argc(&parsed[i]));
		if (!temp)
		{
			free(parsed);
			parsing_error(MALLOC_ERR);
			return (1);
		}
		temp = temp->next;
		free(parsed[i]);
		i++;
	}
	return (0);	
}

char **parsing_input(char *input)
{
	char	**parsed;
	int		nbr_args;

	nbr_args = get_nbr_parsed_args(input, 0, 0) + 1; //plus one to terminate
	parsed = malloc(sizeof(char *) * nbr_args);
	if (!parsed)
	{
		free(input);
		parsing_error(MALLOC_ERR);
		return (NULL);
	}
	if (fill_array(input, parsed, nbr_args))
		return (NULL);
	free(input);
	return (parsed);
}



t_statement	*parsing(char *input)
{
	char	**parsed;
	t_statement	*temp;
	t_statement *new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	parsed = parsing_input(input);
	if (!parsed)
		return (NULL);
	temp = p_new_node(get_argc(&parsed[0]));
	if (!temp)
	{
		free(parsed);
		parsing_error(MALLOC_ERR);
		return (NULL);
	}
	new = temp;
	if (make_statement_list(temp, parsed, i))
		return (NULL);
	free(parsed);
	return (new);
}