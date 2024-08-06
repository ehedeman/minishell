/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 15:45:16 by ehedeman          #+#    #+#             */
/*   Updated: 2024/08/06 15:05:59 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_operator	get_operator(char *operator)
{
	t_operator	op;

	if (!operator)
		op = NONE;
	else if (!ft_strncmp(operator, "|", 1))
		op = PIPE;
	else if (!ft_strncmp(operator, ">>", 2))
		op = RDR_OUT_APPEND;
	else if (!ft_strncmp(operator, ">", 1))
		op = RDR_OUT_REPLACE;
	else if (!ft_strncmp(operator, "<<", 2))
		op = RDR_INPUT_UNTIL;
	else if (!ft_strncmp(operator, "<", 1))
		op = RDR_INPUT;
	else
		op = NONE;
	return (op);
}

int	check_doubles(char *input, int i)
{
	if (is_onstr(QUOTES, input[i]) && input[i] == input[i + 1])
		return (2);
	else if (is_onstr(OPERATORS, input[i]) && input[i] == input[i + 1])
		return (2);
	else if (is_onstr(OPERATORS, input[i]))
		return (1);
	else
		return (0);
}

int	is_spaces(char c)
{
	if (c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r' || c == ' ')
		return (1);
	return (0);
}

int	is_onstr(const char *str, int c)
{
	int	i;

	if (!str)
		return (-1);
	if (!c)
		return (-1);
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	get_argc(char **parsed)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (is_onstr(OPERATORS, parsed[i][0]))
		i++;
	while (parsed[i])
	{
		if (is_onstr(OPERATORS, parsed[i][0]))
			break ;
		count++;
		i++;
	}
	return (count);
}
