/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 11:59:27 by ehedeman          #+#    #+#             */
/*   Updated: 2024/04/09 15:35:23 by ehedeman         ###   ########.fr       */
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

void    reaction_y(void);
void    reaction_n(void);
void    ft_ls(void);
void    ft_pwd(void);
void    ft_cd(char *new_path);
// void    ft_print_history(void);