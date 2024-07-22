/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatschu <smatschu@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 22:23:35 by smatschu          #+#    #+#             */
/*   Updated: 2024/07/22 22:54:09 by smatschu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//For each arg:
//	If arg starts with '$':
//	-Extract the variable name (like, "PATH")
//	-Retrieve the value of "PATH" from the environment variables
//	-Replace "$PATH" in args with its value

#include "minishell.h"

void	*ft_resize_mem(void *ptr, size_t new_size)
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
		*new_arg = ft_resize_mem(*new_arg, new_len + val_len + 1);
		ft_strlcat(*new_arg, var_value, new_len + val_len + 1);
	}
}

char	*expand_arg(char *arg, t_mini *mini)
{
	char	*new_arg;
	int		use_braces;
	char	*var_name;
	char	*var_value;
	char	*exit_status;
	size_t	len;

	new_arg = ft_calloc(1, 1);
	while (*arg)
	{
		if (*arg == '$')
		{
			arg++;
			use_braces = (*arg == '{');
			if (use_braces)
				arg++;
			if (*arg == '?')
			{
				exit_status = ft_itoa(mini->exit_status);
				append_var_value(&new_arg, exit_status);
				free(exit_status);
				arg++;
				if (use_braces && *arg == '}')
					arg++;
			}
			else
			{
				var_name = extract_var_name(&arg);
				if (use_braces && *arg == '}')
					arg++;
				var_value = get_env_value(var_name, mini);
				append_var_value(&new_arg, var_value);
				free(var_name);
			}
		}
		else
		{
			len = ft_strlen(new_arg);
			new_arg = realloc(new_arg, len + 2);
			new_arg[len] = *arg;
			new_arg[len + 1] = '\0';
			arg++;
		}
	}
	return (new_arg);
}

void	replace_env_vars(char **args, t_mini *mini)
{
	char	*new_arg;
	int		i;

	i = 0;
	while (args[i] != NULL)
	{
		new_arg = expand_arg(args[i], mini);
		free(args[i]);
		args[i] = new_arg;
		i++;
	}
}
