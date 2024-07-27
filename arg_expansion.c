/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatschu <smatschu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 22:23:35 by smatschu          #+#    #+#             */
/*   Updated: 2024/07/27 17:20:40 by smatschu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_single_quote(char *start, char **new_arg, size_t *new_arg_len, size_t *new_arg_capacity)
{
	char	*end;
	size_t	segment_len;

	end = ft_strchr(start + 1, '\'');
	if (end == NULL)
		end = start + ft_strlen(start);
	segment_len = end - start - 1;
	if (*new_arg_len + segment_len + 1 > *new_arg_capacity)
	{
		*new_arg_capacity = *new_arg_len + segment_len + 1;
		*new_arg = ft_resize_mem(*new_arg, *new_arg_capacity);
	}
	ft_strlcpy(*new_arg + *new_arg_len, start + 1, segment_len + 1);
	*new_arg_len += segment_len;
	return (end + 1);
}

char	*handle_double_quote(char *start, t_mini *mini, char **new_arg, size_t *new_arg_len, size_t *new_arg_capacity)
{
	char	*end;
	char	*temp;
	char	*expanded;
	size_t	expanded_len;

	end = ft_strchr(start + 1, '"');
	if (end == NULL)
		end = start + ft_strlen(start);
	temp = ft_substr(start, 1, end - start - 1);
	expanded = expand_arg(temp, mini);
	expanded_len = ft_strlen(expanded);
	if (*new_arg_len + expanded_len + 1 > *new_arg_capacity)
	{
		*new_arg_capacity = *new_arg_len + expanded_len + 1;
		*new_arg = ft_resize_mem(*new_arg, *new_arg_capacity);
	}
	ft_strlcpy(*new_arg + *new_arg_len, expanded, expanded_len + 1);
	*new_arg_len += expanded_len;
	free(temp);
	free(expanded);
	return (end + 1);
}

char	*handle_plain_text(char *start, t_mini *mini, char **new_arg, size_t *new_arg_len, size_t *new_arg_capacity)
{
	char	*end;
	char	*temp;
	char	*expanded;
	size_t	expanded_len;

	end = find_next_quote_or_end(start, "'\"");
	if (end == NULL)
		end = start + ft_strlen(start);
	temp = ft_substr(start, 0, end - start);
	expanded = expand_arg(temp, mini);
	expanded_len = ft_strlen(expanded);
	if (*new_arg_len + expanded_len + 1 > *new_arg_capacity)
	{
		*new_arg_capacity = *new_arg_len + expanded_len + 1;
		*new_arg = ft_resize_mem(*new_arg, *new_arg_capacity);
	}
	ft_strlcpy(*new_arg + *new_arg_len, expanded, expanded_len + 1);
	*new_arg_len += expanded_len;
	free(temp);
	free(expanded);
	return (end);
}

char	*process_arg(char *arg, t_mini *mini)
{
	size_t	len;
	size_t	new_arg_capacity;
	char	*new_arg;
	size_t	new_arg_len;
	char	*start;

	len = ft_strlen(arg);
	new_arg_capacity = len + 1;
	new_arg = (char *)malloc(new_arg_capacity);
	new_arg[0] = '\0';
	new_arg_len = 0;
	start = arg;
	while (*start)
	{
		if (*start == '\'')
			start = handle_single_quote(start, &new_arg, &new_arg_len, &new_arg_capacity);
		else if (*start == '"')
			start = handle_double_quote(start, mini, &new_arg, &new_arg_len, &new_arg_capacity);
		else
			start = handle_plain_text(start, mini, &new_arg, &new_arg_len, &new_arg_capacity);
	}
	free(arg);
	return (new_arg);
}

void	replace_env_vars(char **args, t_mini *mini)
{
	int		i;

	i = 0;
	while (args[i] != NULL)
	{
		if (ft_strcmp(args[i], "'$?'") == 0)
		{
			i++;
			continue ;
		}
		args[i] = process_arg(args[i], mini);
		i++;
	}
}
