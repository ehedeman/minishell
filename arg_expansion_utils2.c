/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_expansion_utils2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatschu <smatschu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 17:11:22 by smatschu          #+#    #+#             */
/*   Updated: 2024/07/27 18:31:29 by smatschu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

char	*find_next_quote_or_end(char *str, const char *delim)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_strchr(delim, str[i]))
			return (&str[i]);
		i++;
	}
	return (NULL);
}

char	*handle_dollar_cases(char **arg, t_mini *mini, char *new_arg)
{
	int		use_braces;
	char	*pid_str;

	use_braces = (**arg == '{');
	if (use_braces)
		(*arg)++;
	if (**arg == '?')
		new_arg = handle_exstat(arg, mini, new_arg, use_braces);
	else if (**arg == '$')
	{
		pid_str = ft_itoa(getpid());
		append_var_value(&new_arg, pid_str);
		free(pid_str);
		(*arg)++;
		if (use_braces && **arg == '}')
			(*arg)++;
	}
	else if (**arg == '\0')
		new_arg = append_char_to_new_arg(new_arg, '$');
	else
		new_arg = handle_var_exp(arg, mini, new_arg, use_braces);
	return (new_arg);
}

char	*expand_arg(char *arg, t_mini *mini)
{
	char	*new_arg;

	new_arg = ft_calloc(1, 1);
	while (*arg)
	{
		if (*arg == '$')
		{
			arg++;
			new_arg = handle_dollar_cases(&arg, mini, new_arg);
		}
		else
		{
			new_arg = append_char_to_new_arg(new_arg, *arg);
			arg++;
		}
	}
	return (new_arg);
}
