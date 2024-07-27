/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatschu <smatschu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 19:14:29 by smatschu          #+#    #+#             */
/*   Updated: 2024/07/27 17:02:17 by smatschu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_free_matrix(char **matrix)
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

static int	ft_env_list_comp(t_env_list *env, char **val)
{
	t_env_list	*temp;

	temp = env;
	while (temp != NULL)
	{
		if ((ft_strncmp(temp->name, val[0], ft_strlen(val[0])) == 0))
		{
			if (val[1] != NULL)
			{
				free(temp->value);
				temp->value = ft_strdup(val[1]);
			}
			return (0);
		}
		temp = temp->next;
	}
	return (1);
}

static int	ft_export_add(t_mini *mini, t_env_list *tmp, t_env_list *new, int i)
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
		ft_env_lst_addback(&tmp, new);
		ft_free_matrix(val);
	}
	else
	{
		ft_free_matrix(val);
		return (1);
	}
	return (0);
}

static int	ft_export(t_mini *mini)
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
		ft_print_export_list(temp);
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

int	check_export(t_statement *temp, t_mini *mini, int i)
{
	if (!ft_strncmp(temp->argv[i], "export", ft_strlen("export") + 1))
	{
		ft_export(mini);
		return (1);
	}
	return (0);
}
