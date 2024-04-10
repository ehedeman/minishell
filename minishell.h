/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 12:15:15 by ehedeman          #+#    #+#             */
/*   Updated: 2024/04/10 12:51:43 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

void	ft_ls(void);
void	ft_pwd(void);
void	ft_cd(char *new_path);
void	redirect(char *filename, char *input, int red_type);

typedef struct	s_mini
{
	char *input;
	int bool_redirect;
}				t_mini;