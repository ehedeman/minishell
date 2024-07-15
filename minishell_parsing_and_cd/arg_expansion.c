/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatschu <smatschu@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 22:23:35 by smatschu          #+#    #+#             */
/*   Updated: 2024/07/14 17:18:38 by smatschu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//For each arg:
//	If arg starts with '$':
//	-Extract the variable name (like, "PATH")
//	-Retrieve the value of "PATH" from the environment variables
//	-Replace "$PATH" in args with its value

#include "minishell.h"

// Check if an argument starts with '$'
int	starts_with_dollar(const char *arg)
{
	return (arg[0] == '$');
}

// Extract the variable name from an argumentm skip the $
char	*extract_var_name(const char *arg)
{
	if (starts_with_dollar(arg))
	{
		return (ft_strdup(arg + 1));
	}
	return (NULL);
}

//if you find the var, return its value, if not null
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

// Replace environment variables in args
void	replace_env_vars(char **args, t_mini *mini)
{
	int		i;
	char	*var_name;
	char	*var_value;

	i = 0;
	while (args[i] != NULL)
	{
		if (starts_with_dollar(args[i]))
		{
			var_name = extract_var_name(args[i]);
			if (var_name != NULL)
			{
				var_value = get_env_value(var_name, mini);
				if (var_value != NULL)
				{
					free(args[i]);
					args[i] = ft_strdup(var_value);
				}
				free(var_name);
			}
		}
		i++;
	}
}
