/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_make_statement_list.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatschu <smatschu@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 13:09:03 by ehedeman          #+#    #+#             */
/*   Updated: 2024/08/07 21:52:04 by smatschu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	make_statement_list_1(t_statement *current, char **parsed, \
	int *i, int *j)
{
	while (parsed[*i] && !is_onstr(OPERATORS, parsed[*i][0]))
	{
		current->argv[*j] = remove_quotes(parsed[*i]);
		if (current->argv[*j] == NULL)
			return (1);
		*i += 1;
		*j += 1;
	}
	return (0);
}

int	make_statement_list(t_statement *current, char **parsed, int i)
{
	int	j;

	current->previous = NULL;
	while (parsed[i])
	{
		j = 0;
		if (make_statement_list_1(current, parsed, &i, &j))
			return (1);
		current->argv[j] = NULL;
		if (!parsed[i])
			break ;
		current->operator = get_operator(parsed[i]);
		current->next = p_new_node(get_argc(&parsed[i]));
		if (!current)
		{
			free(parsed);
			parsing_error(MALLOC_ERR);
			return (1);
		}
		current->next->previous = current;
		current = current->next;
		free(parsed[i]);
		i += 1;
	}
	return (0);
}
