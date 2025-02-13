/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatschu <smatschu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 22:23:35 by smatschu          #+#    #+#             */
/*   Updated: 2024/08/09 11:41:56 by smatschu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_single_quote(char *start, t_arg_info *arg_info)
{
	char	*end;
	size_t	segment_len;

	end = ft_strchr(start + 1, '\'');
	if (end == NULL)
		end = start + ft_strlen(start);
	segment_len = end - start - 1;
	if (arg_info->new_arg_len + segment_len + 1 > arg_info->new_arg_capacity)
	{
		arg_info->new_arg_capacity = arg_info->new_arg_len + segment_len + 1;
		arg_info->new_arg = ft_resize_mem(arg_info->new_arg,
				arg_info->new_arg_len, arg_info->new_arg_capacity);
	}
	ft_strlcpy(arg_info->new_arg + arg_info->new_arg_len, start + 1,
		segment_len + 1);
	arg_info->new_arg_len += segment_len;
	return (end + 1);
}

char	*handle_double_quote(char *start, t_mini *mini, t_arg_info *arg_info)
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
	if (arg_info->new_arg_len + expanded_len + 1 > arg_info->new_arg_capacity)
	{
		arg_info->new_arg_capacity = arg_info->new_arg_len + expanded_len + 1;
		arg_info->new_arg = ft_resize_mem(arg_info->new_arg,
				arg_info->new_arg_len, arg_info->new_arg_capacity);
	}
	ft_strlcpy(arg_info->new_arg + arg_info->new_arg_len, expanded,
		expanded_len + 1);
	arg_info->new_arg_len += expanded_len;
	free(temp);
	free(expanded);
	return (end + 1);
}

char	*handle_plain_text(char *start, t_mini *mini, t_arg_info *arg_info)
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
	if (arg_info->new_arg_len + expanded_len + 1 > arg_info->new_arg_capacity)
	{
		arg_info->new_arg_capacity = arg_info->new_arg_len + expanded_len + 1;
		arg_info->new_arg = ft_resize_mem(arg_info->new_arg,
				arg_info->new_arg_len, arg_info->new_arg_capacity);
	}
	ft_strlcpy(arg_info->new_arg + arg_info->new_arg_len, expanded,
		expanded_len + 1);
	arg_info->new_arg_len += expanded_len;
	free(temp);
	free(expanded);
	return (end);
}

char	*process_arg(char *arg, t_mini *mini)
{
	size_t		len;
	t_arg_info	arg_info;
	char		*start;

	len = ft_strlen(arg);
	arg_info.new_arg_capacity = len + 1;
	arg_info.new_arg = (char *)malloc(arg_info.new_arg_capacity);
	arg_info.new_arg[0] = '\0';
	arg_info.new_arg_len = 0;
	start = arg;
	while (*start)
	{
		if (*start == '\'')
			start = handle_single_quote(start, &arg_info);
		else if (*start == '"')
			start = handle_double_quote(start, mini, &arg_info);
		else
			start = handle_plain_text(start, mini, &arg_info);
	}
	free(arg);
	return (arg_info.new_arg);
}

void	replace_env_vars(t_mini *mini)
{
	int			i;
	t_statement	*current;

	i = 0;
	current = mini->com_tab;
	while (current)
	{
		i = 0;
		while (current->argv[i] != NULL)
		{
			if (ft_strcmp(current->argv[i], "'$?'") == 0)
			{
				i++;
				continue ;
			}
			current->argv[i] = process_arg(current->argv[i], mini);
			i++;
		}
		current = current->next;
	}
}
