/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_expansion_utils3.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatschu <smatschu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 18:52:54 by smatschu          #+#    #+#             */
/*   Updated: 2024/08/09 11:42:25 by smatschu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_dollar_sign(char *arg, t_mini *mini, char **new_arg)
{
	int	use_braces;

	arg++;
	if (*arg == '\0' || *arg == '"' || (!ft_isalnum(*arg) && \
		*arg != '{' && *arg != '}' && *arg != '?'))
	{
		*new_arg = append_char_to_new_arg(*new_arg, '$');
		return (arg);
	}
	if (*arg == '$')
	{
		arg++;
		return (arg);
	}
	use_braces = (*arg == '{');
	if (use_braces)
		arg++;
	if (*arg == '?')
		*new_arg = handle_exstat(&arg, mini, *new_arg, use_braces);
	else
		*new_arg = handle_var_exp(&arg, mini, *new_arg, use_braces);
	return (arg);
}
