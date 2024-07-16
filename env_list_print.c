/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 20:14:40 by smatschu          #+#    #+#             */
/*   Updated: 2024/07/15 16:15:49 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//in Bash env prints the var in the order they were defined in the environment
int	ft_print_env_lst(t_env_list *env)
{
	t_env_list	*node;

	node = env;
	if (node == NULL)
		return (1);
	while (node)
	{
		if (node->value != NULL)
			printf("%s=%s\n", node->name, node->value);
		node = node->next;
	}
	return (0);
}

//export prints in alphabetical order
void	print_export_list(t_env_list *sorted_env)
{
	t_env_list	*node;

	node = sorted_env;
	while (node)
	{
		if (node->name[0] != '_')
		{
			if (node->value != NULL && ft_strcmp(node->value, "") != 0)
				printf("declare -x %s=\"%s\"\n", node->name, node->value);
			else if (node->value != NULL && node->value[0] == '\0')
				printf("declare -x %s=\n", node->name);
			else
				printf("declare -x %s\n", node->name);
		}
		node = node->next;
	}
	ft_env_lst_clear(node, free);
}
