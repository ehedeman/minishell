/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_in_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 11:31:59 by ehedeman          #+#    #+#             */
/*   Updated: 2024/07/31 13:15:05 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	rm_invisible_file(t_mini *mini, char **input)
{
    t_statement *rm_node;

	rm_node = create_rm_node(); // creates node with rm and invisible file name
	exec_command(rm_node, mini, 0);
	free_node_input(rm_node, input);
}

