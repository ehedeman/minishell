/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatschu <smatschu@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 13:10:38 by ehedeman          #+#    #+#             */
/*   Updated: 2024/08/07 22:01:04 by smatschu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_statement	*parsing(char *input)
{
	char		**parsed;
	t_statement	*temp;
	t_statement	*new;
	int			i;

	i = 0;
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
	index_list(new);
	return (new);
}
