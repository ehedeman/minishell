/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:00:23 by ehedeman          #+#    #+#             */
/*   Updated: 2024/04/09 14:14:52 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void    reaction_n(void)
{
    printf("rightfully so.\n");
}

void    reaction_y(void)
{
    printf("Liar!\n");
}

void    ft_ls(void)
{
    printf("works\n");
}

void    ft_pwd(void)
{
    char    *path;

    path = malloc(PATH_MAX + 1);
    if (!getcwd(path, PATH_MAX + 1))
        return ;
    printf("%s\n", path);
    free(path);
}

void    ft_cd(char *new_path)
{
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