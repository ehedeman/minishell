/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatschu <smatschu@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 15:54:38 by smatschu          #+#    #+#             */
/*   Updated: 2024/08/07 18:44:16 by smatschu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_join_env(char *env_var)
{
	int		index;
	int		len;
	char	**pair;

	index = 0;
	len = ft_strlen(env_var);
	pair = malloc(sizeof(char *) * 3);
	if (!pair)
		return (NULL);
	while (env_var[index] && env_var[index] != '=')
		index++;
	pair[0] = ft_substr(env_var, 0, index);
	if (index < len)
		pair[1] = ft_substr(env_var, index + 1, len - index - 1);
	else
		pair[1] = NULL;
	pair[2] = NULL;
	return (pair);
}

t_env_list	*copy_linked_list(t_env_list *env)
{
	t_env_list	*current;
	t_env_list	*new_head;
	t_env_list	*new_node;

	current = env;
	new_head = NULL;
	new_node = NULL;
	while (current)
	{
		new_node = ft_env_lst_new(current->name, current->value);
		if (!new_node)
		{
			ft_env_lst_clear(new_head, free);
			return (NULL);
		}
		ft_env_lst_addback(&new_head, new_node);
		current = current->next;
	}
	return (new_head);
}

void	ft_swap_env_nodes(t_env_list *a, t_env_list *b)
{
	char	*temp_name;
	char	*temp_value;

	temp_name = a->name;
	temp_value = a->value;
	a->name = b->name;
	a->value = b->value;
	b->name = temp_name;
	b->value = temp_value;
}

void	sort_linked_list(t_env_list *temp_env)
{
	int			swapped;
	t_env_list	*ptr1;
	t_env_list	*lptr;

	swapped = 1;
	lptr = NULL;
	if (!temp_env)
		return ;
	while (swapped)
	{
		swapped = 0;
		ptr1 = temp_env;
		while (ptr1->next != lptr)
		{
			if (ft_strcmp(ptr1->name, ptr1->next->name) > 0)
			{
				ft_swap_env_nodes(ptr1, ptr1->next);
				swapped = 1;
			}
			ptr1 = ptr1->next;
		}
		lptr = ptr1;
	}
}
