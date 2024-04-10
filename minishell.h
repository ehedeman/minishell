/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 12:15:15 by ehedeman          #+#    #+#             */
/*   Updated: 2024/04/10 14:42:13 by ehedeman         ###   ########.fr       */
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
#include <sys/stat.h>

typedef struct	s_mini
{
	char	*input;
	int 	redirect;
	mode_t 	mode;
}				t_mini;

void	ft_ls(void);
void	ft_pwd(t_mini *mini);
void	ft_cd(char *new_path);
void	file_write(char *filename, char *input, int red_type, t_mini *mini);
int		create_file(char *filename, t_mini *mini);
void	ft_exit(t_mini *mini);
