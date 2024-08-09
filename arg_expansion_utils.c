/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_expansion_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatschu <smatschu@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 14:48:18 by smatschu          #+#    #+#             */
/*   Updated: 2024/08/07 18:43:37 by smatschu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_resize_mem(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);
	if (ptr)
	{
		if (old_size < new_size)
			ft_memcpy(new_ptr, ptr, old_size);
		else
			ft_memcpy(new_ptr, ptr, new_size);
		free(ptr);
	}
	return (new_ptr);
}

char	*get_env_value(const char *var_name, t_mini *mini)
{
	t_env_list	*current;

	current = mini->env;
	while (current != NULL)
	{
		if (ft_strcmp(current->name, var_name) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

char	*extract_var_name(char	**arg)
{
	char	*start_var;
	char	*var_name;
	size_t	name_len;

	start_var = *arg;
	while (**arg && (ft_isalnum(**arg) || **arg == '_'))
		(*arg)++;
	name_len = *arg - start_var;
	var_name = ft_calloc(name_len + 1, 1);
	ft_strlcpy(var_name, start_var, name_len + 1);
	var_name[name_len] = '\0';
	return (var_name);
}

void	append_var_value(char **new_arg, const char *var_value)
{
	int	new_len;
	int	val_len;

	if (var_value != NULL)
	{
		new_len = ft_strlen(*new_arg);
		val_len = ft_strlen(var_value);
		*new_arg = ft_resize_mem(*new_arg, new_len + 1, new_len + val_len + 1);
		ft_strlcat(*new_arg, var_value, new_len + val_len + 1);
	}
}
