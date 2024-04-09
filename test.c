/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 11:59:49 by ehedeman          #+#    #+#             */
/*   Updated: 2024/04/09 14:19:31 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int main()
{
    char    *str;

    while (1)
    {
        str = readline("Minishell: ");
        if (!str)
        {
            write(2, "Error\n", 6);
            return (0);
        }
        add_history(str);
        if (ft_strnstr(str, "ls", ft_strlen(str)))
            ft_ls();  
        else if (ft_strncmp(str, "pwd", ft_strlen(str)) == 0)
            ft_pwd();
        else if (ft_strnstr(str, "cd", ft_strlen(str)))
            ft_cd(str);
        free(str);
    }
    return (0);
}