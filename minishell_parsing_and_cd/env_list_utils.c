/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatschu <smatschu@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:46:10 by smatschu          #+#    #+#             */
/*   Updated: 2024/07/10 11:27:37 by smatschu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//this will create a new node for the linked list
t_env_list *ft_env_lst_new(char *key, char *value)
{
	t_env_list	*node;

	node = (t_env_list *)malloc(sizeof(t_env_list));
	if (!node)
		return (NULL);
	node->name = ft_strdup(key);
	node->value = ft_strdup(value);
	node->next = NULL;
	//free(key);
	//free(value);
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
		//printf("new node: %s\n", new->name);
		//printf("new node: %s\n", new->value);
		// while((*lst)->next)
		// {
		// 	printf("list->next: %s\n", (*lst)->next->name);
		// 	printf("list->next: %s\n", (*lst)->next->value);
		// }
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
void ft_env_lst_clear(t_env_list *lst, void (*del)(void *))
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

