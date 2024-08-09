/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_out.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatschu <smatschu@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 11:24:36 by ehedeman          #+#    #+#             */
/*   Updated: 2024/08/07 22:00:58 by smatschu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_path(char *path)
{
	if (path[0] == '.' && path[1] == '/' && path[3])
		return (1);
	else if (!ft_strncmp("/home", path, 5))
		return (1);
	return (0);
}

static int	set_fd(char *filename, int red_type)
{
	int		fd;
	mode_t	mode;

	mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	fd = 0;
	if (red_type == 1)
		fd = open(filename, O_RDWR | O_CREAT | O_APPEND, mode);
	else if (red_type == 2)
		fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, mode);
	if (fd < 0)
		main_error(-1);
	return (fd);
}

int	get_fd(t_statement *temp)
{
	char	*temp_path;
	int		need_free;
	int		fd;

	need_free = 0;
	temp_path = NULL;
	if (!is_path(temp->next->argv[0]))
	{
		temp_path = ft_strjoin("./", temp->next->argv[0]);
		if (!temp_path)
			return (main_error(MALLOC_ERR));
		need_free = 1;
	}
	else
		temp_path = temp->next->argv[0];
	if (temp->operator == RDR_OUT_REPLACE)
		fd = set_fd(temp_path, 2);
	else if (temp->operator == RDR_OUT_APPEND)
		fd = set_fd(temp_path, 1);
	else
		fd = 1;
	if (need_free)
		free(temp_path);
	return (fd);
}
