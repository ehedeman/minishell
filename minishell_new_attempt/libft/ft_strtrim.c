/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 13:04:23 by ehedeman          #+#    #+#             */
/*   Updated: 2023/11/23 12:37:17 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	in_set(char *set, char s)
{
	while (*set)
	{
		if (*set == s)
			return (0);
		set++;
	}
	return (1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*new;
	int		end;
	int		start;

	if (!s1)
		return (NULL);
	if (!*s1)
		return (ft_strdup(""));
	if (!set || !*set)
		return (ft_strdup((char *)s1));
	start = 0;
	end = ft_strlen(s1);
	while (!in_set((char *)set, s1[start]))
		start++;
	if (start == (int)ft_strlen((char *)s1))
	{
		new = ft_strdup("");
		return (new);
	}
	while (!in_set((char *)set, s1[end - 1]))
		end--;
	new = ft_substr((char *)s1, start, end - start);
	return (new);
}

// int main()
// {
// 	char *a;
// 	a = ft_strtrim("   xxx   xxx", " x");
// 	printf("output  %s ", a );
// 	free(a);
// }