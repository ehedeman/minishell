/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:19:48 by ehedeman          #+#    #+#             */
/*   Updated: 2024/07/01 15:13:59 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
int	is_spaces(char c)
{
	if (c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r' || c == ' ')
		return (1);
	return (0);
}

int	get_nbr_statements(char *input, int i)
{
	int	count;
	bool quotes;

	count = 0;
	quotes = false;
	while (input[i])
	{
		if (is_onstr(OPERATORS, input[i]))
		{
			if (is_onstr(OPERATORS, input[i + 1]))
				i++;
			count++;
		}
		if (is_onstr(QUOTES, input[i]) && input[i] == input[i + 1])
			i++;
		else if (is_onstr(QUOTES, input[i]))
			quotes = !quotes;
		if (input[i] != ' ' && !is_onstr(OPERATORS, input[i]))
		{
			count++;
			while (input[i + 1] && !is_onstr(OPERATORS, input[i + 1]))
			{
				if (is_spaces(input[i]) && !quotes)
					break ;
				i++;
			}
		}
		i++;
	}
	return (count);
}

int	get_token_len(char *input)
{
	int	i;
	int size;
	bool quotes;

	quotes = false;
	i = 0;
	size = 0;
	if (is_onstr(OPERATORS, input[i]))
	{
		if (input[i] == input[i + 1])
			return (2);
		return (1);
	}
	while (is_spaces(input[i]))
		i++;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
			quotes = !quotes;
		if (is_spaces(input[i]) && !quotes)
			break ;
		if (is_onstr(OPERATORS, input[i]))
			return (size);
		size++;
		i++;
	}
	return (size);
}
//		printf("%c %i\n", input[i], size);
char **parsing_input(char *input, int i, int j, int k)
{
	char	**parsed;
	int		length;
	bool quotes;
	
	quotes = false;
	parsed = malloc(sizeof(char *) * (get_nbr_statements(input, 0) + 1));
	if (!parsed)
	{
		free(input);
		parsing_error(MALLOC_ERR);
		return (NULL);
	}
	while (input[i])
	{
		k = 0;
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
			return (NULL);
		}
		while (input[i] && k < length)
		{
			if (input[i] == '\'' || input[i] == '\"')
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
		j++;
	}
	parsed[j] = NULL;
	return (parsed);
}

void print_p(char **parsed, int j)
{
	int i = 0;
	printf("j: %i\n", j);
	while (parsed[i])
	{
		printf("print_p: %s\n", parsed[i]);
		i++;
	}
	printf("\n");
}

t_statement *parsing(char *input, int i, int j)
{
	char	**parsed;
	t_statement	*temp;
	t_statement	*head;

	parsed = parsing_input(input, 0, 0, 0);
	if (!parsed)
		return (NULL);
	free(input);
	temp = p_new_node(get_argc(&parsed[0]));
	if (!temp)
	{
		free(parsed);
		parsing_error(MALLOC_ERR);
		return (NULL);
	}
	head = temp;
	i = 0;
	while (parsed[i])
	{
		j = 0;
		while (parsed[i] && !is_onstr(OPERATORS, parsed[i][0]))
		{
			temp->argv[j] = remove_quotes(parsed[i]);
			if (temp->argv[j] == NULL)
				return (NULL);
			i++;
			j++;
		}
		temp->argv[j] = NULL;
		if (!parsed[i])
			break ;
		temp->operator = get_operator(parsed[i]);
		temp->next = p_new_node(get_argc(&parsed[i]));
		temp->next->operator = SKIP;
		if (!temp)
		{
			free(parsed);
			parsing_error(MALLOC_ERR);
			return (NULL);
		}
		temp = temp->next;
		free(parsed[i]);
		i++;
	}
	temp->next = NULL;
	free(parsed);
	return (head);
}
