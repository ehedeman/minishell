/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 14:46:10 by smatschu          #+#    #+#             */
/*   Updated: 2024/07/08 09:56:28 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_print_env_lst(t_env_list *env)
{
	t_env_list	*node;

	node = env;
	if (node == NULL)
		return (1);
	while (node)
	{
		printf("%s=%s\n", node->name, node->value);
		node = node->next;
	}
	return (0);
}

t_env_list	*ft_create_node(char *env_var)
{
	t_env_list	*new_node;
	int			i;
	int			len;

	i = 0;
	len = ft_strlen(env_var);
	while (env_var[i] && env_var[i] != '=')
		i++;
	new_node = ft_env_lst_new(ft_substr(env_var, 0, i), ft_substr(env_var, i + 1, len));
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

//env list functions
t_env_list *ft_env_lst_new(char *key, char *value)
{
	t_env_list	*node;

	node = (t_env_list *)malloc(sizeof(t_env_list));
	if (!node)
		return (NULL);
	node->name = ft_strdup(key);
	node->value = ft_strdup(value);
	node->next = NULL;
	free(key);
	free(value);
	return (node);
}

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
