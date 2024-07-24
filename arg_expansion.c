/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatschu <smatschu@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 22:23:35 by smatschu          #+#    #+#             */
/*   Updated: 2024/07/24 14:51:56 by smatschu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//For each arg:
//	If arg starts with '$':
//	-Extract the variable name (like, "PATH")
//	-Retrieve the value of "PATH" from the environment variables
//	-Replace "$PATH" in args with its value

#include "minishell.h"

char	*append_char_to_new_arg(char *new_arg, char arg_char)
{
	size_t	len;

	len = ft_strlen(new_arg);
	new_arg = ft_resize_mem(new_arg, len + 2);
	new_arg[len] = arg_char;
	new_arg[len + 1] = '\0';
	return (new_arg);
}

char	*handle_exstat(char **arg, t_mini *mini, char *new_arg, int use_braces)
{
	char	*exit_status;

	exit_status = ft_itoa(mini->exit_status);
	append_var_value(&new_arg, exit_status);
	free(exit_status);
	(*arg)++;
	if (use_braces && **arg == '}')
		(*arg)++;
	return (new_arg);
}

char	*handle_var_exp(char **arg, t_mini *mini, char *new_arg, int use_braces)
{
	char	*var_name;
	char	*var_value;

	var_name = extract_var_name(arg);
	if (use_braces && **arg == '}')
		(*arg)++;
	var_value = get_env_value(var_name, mini);
	append_var_value(&new_arg, var_value);
	free(var_name);
	return (new_arg);
}

char	*expand_arg(char *arg, t_mini *mini)
{
	char	*new_arg;
	int		use_braces;

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
				new_arg = handle_exstat(&arg, mini, new_arg, use_braces);
			else
				new_arg = handle_var_exp(&arg, mini, new_arg, use_braces);
		}
		else
		{
			new_arg = append_char_to_new_arg(new_arg, *arg);
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
