/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatschu <smatschu@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 22:48:44 by smatschu          #+#    #+#             */
/*   Updated: 2024/07/10 11:47:48 by smatschu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//this will search for the target name to unset in the linked list and then free it
int	ft_unset(t_env_list *env, char *target_name)
{
	t_env_list	*temp;

	if (env == NULL || env->next == NULL)
		return (1);
	temp = env;
	if (ft_strncmp(env->next->name, target_name, ft_strlen(target_name)) == 0)
	{
		temp = env->next;
		env->next = temp->next;
		ft_free_env(temp);
	}
	else if (ft_strncmp(env->name, target_name, ft_strlen(target_name)) == 0)
	{
		temp = env;
		env = env->next;
		ft_free_env(temp);
	}
	else
	{
		temp = env;
		ft_unset(temp->next, target_name);
	}
	return(0);
}