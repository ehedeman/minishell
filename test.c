/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 11:59:49 by ehedeman          #+#    #+#             */
/*   Updated: 2024/04/09 13:20:55 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int main()
{
    char    *str;

    str = readline("Minishell: ");
    if (!str)
    {
        write(2, "Error\n", 6);
        return (0);
    }
    if (ft_strnstr(str, "ls", ft_strlen(str)))
       ft_ls();  
    else if (str[0] == 'n')
        reaction_n();
    free(str);
    return (0);
}