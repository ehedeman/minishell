/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_list_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 12:38:26 by ehedeman          #+#    #+#             */
/*   Updated: 2024/07/16 12:47:56 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_statement	*p_new_node(int argc)
{
	t_statement	*new_node;

	new_node = malloc(sizeof(t_statement));
	if (!new_node)
		return (NULL);
	new_node->argc = argc;
	new_node->argv = malloc((argc + 1) * sizeof(char *));
	if (!new_node->argv)
	{
		free(new_node);
		return (NULL);
	}
	new_node->operator = NONE;
	new_node->next = NULL;
	return(new_node);
}