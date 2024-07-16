/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatschu <smatschu@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 22:48:44 by smatschu          #+#    #+#             */
/*   Updated: 2024/07/14 17:23:19 by smatschu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset_free(t_env_list *env_var)
{
	free(env_var->name);
	free(env_var->value);
	free(env_var);
}

//this will search for the target name to unset in the list and then free it
int	ft_unset(t_env_list *env, char *target)
{
	t_env_list	*temp;

	if (env == NULL || env->next == NULL)
		return (1);
	temp = env;
	if (env->next->name && \
		ft_strncmp(env->next->name, target, ft_strlen(target)) == 0)
	{
		temp = env->next;
		env->next = temp->next;
		ft_unset_free(temp);
	}
	else if (env->name && ft_strncmp(env->name, target, ft_strlen(target)) == 0)
	{
		temp = env;
		env = env->next;
		ft_unset_free(temp);
	}
	else
	{
		temp = env;
		ft_unset(temp->next, target);
	}
	return (0);
}
