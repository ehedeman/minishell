/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 14:45:05 by ehedeman          #+#    #+#             */
/*   Updated: 2023/11/22 15:22:10 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*new;

	i = 0;
	if (!s || (!s && !f))
		return (ft_strdup(""));
	else if (!f)
		return (ft_strdup(s));
	new = ft_strdup(s);
	if (!new)
		return (0);
	while (s[i])
	{
		new[i] = f(i, s[i]);
		i++;
	}
	return (new);
}

//char	ft_dosmth(unsigned int c, char a)
//{
//	unsigned int i;
//	i = c;
//	a = a -32;
//	return (a);	
//}
//
//int main()
//{
//	char *a;	
//	a = ft_strmapi("hello", &ft_dosmth);
//	printf("%s", a);
//}
