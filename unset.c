/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatschu <smatschu@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 22:48:44 by smatschu          #+#    #+#             */
/*   Updated: 2024/07/28 18:53:47 by smatschu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_unset_free(t_env_list *env_var)
{
	free(env_var->name);
	free(env_var->value);
	free(env_var);
}

//this will search for the target name to unset in the list and then free it
static int	ft_unset(t_env_list *env, char *target)
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

int	check_unset(t_statement *temp, t_mini *mini, int i)
{
	if (!ft_strncmp(temp->argv[i], "unset", ft_strlen("unset") + 1))
	{
		while (temp->argv[i])
		{
			mini->exit_status = ft_unset(mini->env, temp->argv[i]);
			i++;
		}
		return (1);
	}
	return (0);
}
