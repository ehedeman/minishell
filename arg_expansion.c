/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatschu <smatschu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 22:23:35 by smatschu          #+#    #+#             */
/*   Updated: 2024/07/27 16:33:54 by smatschu         ###   ########.fr       */
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

void	replace_env_vars(char **args, t_mini *mini)
{
	int		i;
	char	*new_arg;
	size_t	len;
	char	*temp;
	char	*start;
	char	*end;
	char	*expanded;
	size_t	new_arg_len;
	size_t	segment_len;
	size_t	expanded_len;
	size_t	new_arg_capacity;

	i = 0;
	while (args[i] != NULL)
	{
		if (ft_strcmp(args[i], "'$?'") == 0)
		{
			i++;
			continue ;
		}
		len = ft_strlen(args[i]);
		new_arg_capacity = len + 1;
		new_arg = (char *)malloc(new_arg_capacity);
		new_arg[0] = '\0';
		new_arg_len = 0;
		start = args[i];
		while (*start)
		{
			if (*start == '\'')
			{
				end = ft_strchr(start + 1, '\'');
				if (end == NULL)
					end = start + ft_strlen(start);
				segment_len = end - start - 1;
				if (new_arg_len + segment_len + 1 > new_arg_capacity)
				{
					new_arg_capacity = new_arg_len + segment_len + 1;
					new_arg = ft_resize_mem(new_arg, new_arg_capacity);
				}
				ft_strlcpy(new_arg + new_arg_len, start + 1, segment_len + 1);
				new_arg_len += segment_len;
				start = end + 1;
			}
			else if (*start == '"')
			{
				end = ft_strchr(start + 1, '"');
				if (end == NULL)
					end = start + ft_strlen(start);
				temp = ft_substr(start, 1, end - start - 1);
				expanded = expand_arg(temp, mini);
				expanded_len = ft_strlen(expanded);
				if (new_arg_len + expanded_len + 1 > new_arg_capacity)
				{
					new_arg_capacity = new_arg_len + expanded_len + 1;
					new_arg = ft_resize_mem(new_arg, new_arg_capacity);
				}
				ft_strlcpy(new_arg + new_arg_len, expanded, expanded_len + 1);
				new_arg_len += expanded_len;
				free(temp);
				free(expanded);
				start = end + 1;
			}
			else
			{
				end = find_next_quote_or_end(start, "'\"");
				if (end == NULL)
					end = start + ft_strlen(start);
				temp = ft_substr(start, 0, end - start);
				expanded = expand_arg(temp, mini);
				expanded_len = ft_strlen(expanded);
				if (new_arg_len + expanded_len + 1 > new_arg_capacity)
				{
					new_arg_capacity = new_arg_len + expanded_len + 1;
					new_arg = ft_resize_mem(new_arg, new_arg_capacity);
				}
				ft_strlcpy(new_arg + new_arg_len, expanded, expanded_len + 1);
				new_arg_len += expanded_len;
				free(temp);
				free(expanded);
				start = end;
			}
		}
		free(args[i]);
		args[i] = new_arg;
		i++;
	}
}
