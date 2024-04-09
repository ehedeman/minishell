/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 11:59:49 by ehedeman          #+#    #+#             */
/*   Updated: 2024/04/09 15:35:09 by ehedeman         ###   ########.fr       */
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
        if (*str)
        {
            add_history(str);
            if (ft_strnstr(str, "ls", ft_strlen(str)))
                ft_ls();  
            else if (ft_strncmp(str, "pwd", ft_strlen(str)) == 0)
                ft_pwd();
            else if (ft_strnstr(str, "cd", ft_strlen(str)))
                ft_cd(str);
            //  else if (ft_strncmp(str, "print history", ft_strlen(str)))
            //     ft_print_history();
            // else if (ft_strnstr(str, "./", ft_strlen(str)))
            //     ft_execute(str);
       }
        free(str);
    }
    return (0);
}