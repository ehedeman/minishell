/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatschu <smatschu@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 19:14:29 by smatschu          #+#    #+#             */
/*   Updated: 2024/07/14 16:48:21 by smatschu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_matrix(char **matrix)
{
	int	index;

	index = 0;
	while (matrix[index])
	{
		free(matrix[index]);
		index++;
	}
	free(matrix);
}

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

int	ft_env_list_comp(t_env_list *env, char **val)
{
	t_env_list	*temp;

	temp = env;
	while (temp != NULL)
	{
		if (ft_strncmp(temp->name, val[0], ft_strlen(val[0])) == 0)
		{
			free(temp->value);
			if (val[1] != NULL)
				temp->value = ft_strdup(val[1]);
			else
				temp->value = NULL;
			return (0);
		}
		temp = temp->next;
	}
	return (1);
}

int	ft_export_add(t_mini *mini, t_env_list *temp, t_env_list *new, int i)
{
	char	**val;

	val = ft_join_env(mini->com_tab->argv[i]);
	if (!val || !val[0])
		return (main_error(MALLOC_ERR));
	if (ft_isalpha(val[0][0]) == 1 && ft_env_list_comp(mini->env, val) != 0)
	{
		new = ft_env_lst_new(val[0], val[1]);
		if (!new)
		{
			ft_free_matrix(val);
			return (1);
		}
		ft_env_lst_addback(&temp, new);
		ft_free_matrix(val);
	}
	else
	{
		ft_free_matrix(val);
		write(2, "export: not a valid identifier\n", 31);
		return (1);
	}
	return (0);
}

int	ft_export(t_mini *mini)
{
	t_env_list	*temp;
	t_env_list	*new;
	int			i;

	i = 0;
	new = NULL;
	if (!mini->com_tab->argv[1])
	{	
		temp = copy_linked_list(mini->env);
		if (!temp)
			return (main_error(MALLOC_ERR));
		sort_linked_list(temp);
		print_export_list(temp);
		ft_env_lst_clear(temp, free);
	}
	else
	{
		temp = mini->env;
		while (mini->com_tab->argv[++i] != NULL)
			if (ft_export_add(mini, temp, new, i) == -1)
				return (1);
	}
	return (0);
}
