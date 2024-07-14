/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatschu <smatschu@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:46:10 by smatschu          #+#    #+#             */
/*   Updated: 2024/07/14 16:59:26 by smatschu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//calculates the lengh of the env list
int	ft_env_list_len(t_env_list *env)
{
	int	count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

//this will create a new node for the linked list
t_env_list	*ft_env_lst_new(char *key, char *value)
{
	t_env_list	*node;

	node = (t_env_list *)malloc(sizeof(t_env_list));
	if (!node)
		return (NULL);
	node->name = ft_strdup(key);
	if (value != NULL && value[0] == '\0')
		node->value = ft_strdup("\0");
	else if (value == NULL)
		node->value = NULL;
	else
		node->value = ft_strdup(value);
	node->next = NULL;
	return (node);
}

//this will add a new node to the end of the linked list
void	ft_env_lst_addback(t_env_list **lst, t_env_list *new)
{
	t_env_list	*node;

	node = *lst;
	if (node == NULL)
		*lst = new;
	else
	{
		while (node->next != NULL)
			node = node->next;
		node->next = new;
	}
}

//this will free one node of the linked list
void	ft_lst_delone(t_env_list *lst, void (*del)(void *))
{
	del(lst->name);
	del(lst->value);
	free(lst);
}

//this will free the linked list (added to the end of ft_exit)
void	ft_env_lst_clear(t_env_list *lst, void (*del)(void *))
{
	t_env_list	*node;

	node = lst;
	while (lst != NULL)
	{
		node = lst->next;
		ft_lst_delone(lst, del);
		lst = node;
	}
	lst = NULL;
}
