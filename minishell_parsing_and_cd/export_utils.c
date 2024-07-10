/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatschu <smatschu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 15:54:38 by smatschu          #+#    #+#             */
/*   Updated: 2024/07/10 16:50:51 by smatschu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	swap(char **a, char **b) {
	char *temp = *a;
	*a = *b;
	*b = temp;
}

void	sort_env_array(char **arr, int n) {
	int i, j;
	int swapped;
	i = 0;
	while (i < n - 1) {
		j = 0;
		swapped = 0;
		while (j < n - i - 1) {
			if (ft_strncmp(arr[j], arr[j + 1], strlen(arr[j]) + 1) > 0) {
				swap(&arr[j], &arr[j + 1]);
				swapped = 1;
			}
			j++;
		}
		if (!swapped) break;
		i++;
	}
}

int	count_env_vars(t_env_list *env) {
	int count = 0;
	while (env) {
		count++;
		env = env->next;
	}
	return count;
}

char	**copy_env_vars(t_env_list *env, int count) {
	char **env_array = (char **)malloc(count * sizeof(char *));
	if (!env_array) {
		perror("malloc");
		return NULL;
	}
	int i = 0;
	while (i < count) {
		env_array[i] = env->name;
		env = env->next;
		i++;
	}
	return (env_array);
}

//env var without value should not be printed by env and only name should be printed by export, without =
void print_sorted_env_vars(t_env_list *env, char **env_array, int count) {
	int i = 0;
	while (i < count) {
		t_env_list *temp = env;
		while (temp) {
			if (ft_strncmp(temp->name, env_array[i], strlen(temp->name) + 1) == 0) {
				if (temp->name[0] != '_')
				{
					if (ft_strncmp(temp->value, "", 1) == 0) 
						ft_printf("declare -x %s\n", temp->name);
					else
						ft_printf("declare -x %s=\"%s\"\n", temp->name, temp->value);
				}
				break;
			}
			temp = temp->next;
		}
		i++;
	}
}