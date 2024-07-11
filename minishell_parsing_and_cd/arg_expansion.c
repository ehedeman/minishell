/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatschu <smatschu@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 22:23:35 by smatschu          #+#    #+#             */
/*   Updated: 2024/07/11 23:05:08 by smatschu         ###   ########.fr       */
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
	return(arg[0] == '$');
}

// Extract the variable name from an argument
char	*extract_var_name(const char *arg)
{
	if (starts_with_dollar(arg))
	{
		return (ft_strdup(arg + 1)); // Skip the '$'
	}
	return (NULL);
}

// Retrieve the value of an environment variable...but from envp, and not from the new envp array in mini, have to fix it.
char *get_env_value(const char *var_name)
{
	return (getenv(var_name)); // Use getenv to get the environment variable value
}

// Replace environment variables in args
void	replace_env_vars(char **args)
{
	int	i;
	char	*var_name;

	i = 0;
	while (args[i] != NULL)
	{
		if (starts_with_dollar(args[i]))
		{
			var_name = extract_var_name(args[i]);
			if (var_name != NULL) {
				char *value = get_env_value(var_name);
				if (value != NULL) {
					free(args[i]); // Free the original arg memory
					args[i] = ft_strdup(value); // Replace with the new value
				}
				free(var_name); // Free the extracted variable name
			}
		}
		i++;
	}
}