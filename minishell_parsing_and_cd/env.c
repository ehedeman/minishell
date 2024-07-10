/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatschu <smatschu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:46:10 by smatschu          #+#    #+#             */
/*   Updated: 2024/07/10 16:52:35 by smatschu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//this will print the linked list
int	ft_print_env_lst(t_env_list *env)
{
	t_env_list	*node;

	node = env;
	if (node == NULL)
		return (1);
	while (node)
	{
		if(ft_strncmp(node->value, "", 1) != 0)
			printf("%s=%s\n", node->name, node->value);
		node = node->next;
	}
	return (0);
}

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
	kv[2] =  NULL;
	new_node = ft_env_lst_new(kv[0], kv[1]);
	free(kv[0]);
	free(kv[1]);
	free(kv[2]);
	free(kv);
	return (new_node);
}

//this will create a linked list with the name and value of the variables in envp (t_env_list *env)
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

