/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatschu <smatschu@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:46:10 by smatschu          #+#    #+#             */
/*   Updated: 2024/07/28 18:54:06 by smatschu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//this will create a new node for the linked list
t_env_list	*ft_create_node(char *env_var)
{
	t_env_list	*new_node;
	int			i;
	int			len;
	char		**kv;

	kv = malloc(sizeof(char *) * 3);
	i = 0;
	len = ft_strlen(env_var);
	while (env_var[i] && env_var[i] != '=')
		i++;
	kv[0] = ft_substr(env_var, 0, i);
	kv[1] = ft_substr(env_var, i + 1, len);
	kv[2] = NULL;
	new_node = ft_env_lst_new(kv[0], kv[1]);
	free(kv[0]);
	free(kv[1]);
	free(kv[2]);
	free(kv);
	return (new_node);
}

//this will create a linked list with the name and
//value of the variables in envp (t_env_list *env)
void	ft_copy_env2lst(t_mini *mini, char **envp)
{
	int			i;
	t_env_list	*node;

	i = 0;
	mini->env = NULL;
	while (envp[i] != NULL)
	{
		node = ft_create_node(envp[i]);
		if (!node)
			perror("Error: could not create node for env list");
		ft_env_lst_addback(&mini->env, node);
		i++;
	}
}

int	check_env(t_statement *temp, t_mini *mini, int i)
{
	if (!ft_strncmp(temp->argv[i], "env", ft_strlen("env") + 1) && \
		!temp->argv[i + 1])
	{
		mini->exit_status = ft_print_env_lst(mini->env);
		return (1);
	}
	return (0);
}
