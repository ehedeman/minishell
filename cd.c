/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 11:23:16 by ehedeman          #+#    #+#             */
/*   Updated: 2024/04/10 12:17:36 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int ft_cd_nothing(char *new_path)
{
    if (ft_strncmp(new_path, "cd", ft_strlen(new_path)) == 0)
    {
        if (chdir(getenv("HOME")) == -1)
            printf("%s\n", strerror(errno));
        return (1);
    }
    return (0);
}

void    ft_cd(char *new_path)
{
    if (ft_cd_nothing(new_path) == 1)
        return ;
    if (new_path[0] != 'c' || new_path[1] != 'd' || new_path[2] != ' ')
        return ;
    while (*new_path)
    {
        if (*new_path == ' ')
        {
            new_path++;
            break ;
        }
        new_path++;
    }
    if (!*new_path)
        return ;
    if (chdir(new_path) == -1)
        printf("%s\n", strerror(errno));
}