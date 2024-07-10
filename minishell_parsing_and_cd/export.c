/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatschu <smatschu@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 19:14:29 by smatschu          #+#    #+#             */
/*   Updated: 2024/07/10 11:30:53 by smatschu         ###   ########.fr       */
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
	while (env_var[index] && env_var[index] != '=')
		index++;
	pair[0] = ft_substr(env_var, 0, index);
	pair[1] = ft_substr(env_var, index + 1, len);
	pair[2] = NULL;
	printf("pair[0]: %s\n", pair[0]);
	printf("pair[1]: %s\n", pair[1]);
	printf("pair[2]: %s\n", pair[2]);
	return (pair);
}

int	ft_env_list_comp(t_env_list *env, char **val)
{
	t_env_list	*temp;

	temp = env;
	if (temp == NULL)
		return (1);
	else if (ft_strncmp(temp->name, val[0], ft_strlen(val[0])) == 0)
	{
		free(temp->value);
		temp->value = ft_strdup(val[1]);
		return (0);
	}
	else
		return (ft_env_list_comp(temp->next, val));
}


int	ft_export_add(t_mini *mini, t_env_list *temp, t_env_list *new, int i)
{
	char	**val;

	val = ft_join_env(mini->com_tab->argv[i]);
	if (!val || !val[0]) // Check if val is NULL or val[0] is NULL
	{
		write(2, "export: error processing arguments\n", 35);
		return (1);
	}
	if (ft_isalpha(val[0][0]) == 1)
	{
		if (ft_env_list_comp(mini->env, val) != 0)
		{
			printf("val[0]: %s\n", val[0]);
			printf("val[1]: %s\n", val[1]);
			new = ft_env_lst_new(val[0], val[1]);
			if(!new)
			{
				ft_free_matrix(val);
				printf("new is NULL\n");
				return (1);
			}
			ft_env_lst_addback(&temp, new);
			//printf("NODE SHOULD BE NOW ADDED TO THE BACK OF LIST\n");
			//ft_print_env_lst(temp);
		}
		ft_free_matrix(val);
	}
	else
	{
		write(2, "export: not a valid identifier\n", 31);
		ft_free_matrix(val);
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
	temp = mini->env; // Use the address of the list head
	if (!mini->com_tab->argv[1])
	{
		while (temp)
		{
			if(temp->name[0] != '_')
			{
				if(ft_strncmp(temp->value, "", 1) == 0) // If value is not "
					ft_printf("declare -x %s\n", temp->name);
				else
					ft_printf("declare -x %s=\"%s\"\n", temp->name, temp->value);
					
			}
			temp = temp->next;
		}
	}
	else
	{
		i = 1;
		while (mini->com_tab->argv[i] != NULL)
		{
			printf("mini->com_tab->argv[%d]: %s\n", i, mini->com_tab->argv[i]);
			if(ft_export_add(mini, temp, new, i) == 1)
				return (1);
			i++;
		}
		// printf("\n\nLIST AFTER EXPORT @ft_export\n");
		// ft_print_env_lst(mini->env);
	}
	return (0);
}