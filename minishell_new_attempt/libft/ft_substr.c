/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 13:02:40 by ehedeman          #+#    #+#             */
/*   Updated: 2023/11/22 14:43:34 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;

	i = 0;
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (!s)
		return (NULL);
	if (len > ft_strlen(s))
		str = (char *)malloc(sizeof(char) * (ft_strlen(s) - start +1));
	else
		str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	while (i < len && s[start])
	{
		str[i] = s[start];
		start++;
		i++;
	}
	str[i] = '\0';
	return (str);
}

//int main()
//{
//	char *a;
//
//	a = ft_substr("hellohowareyou", 5, 9);
//	printf("%s", a );
//	free(a);
//}