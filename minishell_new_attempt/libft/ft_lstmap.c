/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:22:56 by ehedeman          #+#    #+#             */
/*   Updated: 2024/03/06 13:37:31 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*temp;
	t_list	*original_temp;

	if (!lst || !f || !del)
		return (0);
	temp = ft_lstnew(f(lst->content));
	if (!temp)
		return (0);
	original_temp = temp;
	lst = lst->next;
	while (lst)
	{
		temp->next = ft_lstnew(f(lst->content));
		if (!temp->next)
		{
			ft_lstclear(&original_temp, del);
			return (0);
		}
		temp = temp->next;
		lst = lst->next;
	}
	temp->next = NULL;
	return (original_temp);
}
