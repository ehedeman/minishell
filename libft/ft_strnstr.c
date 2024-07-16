/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 15:17:23 by ehedeman          #+#    #+#             */
/*   Updated: 2023/11/23 14:52:18 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, int len)
{
	int		i;
	int		c;
	int		n_len;
	char	*hay_cpy;

	hay_cpy = (char *)haystack;
	if (len < 0)
		len = ft_strlen(hay_cpy);
	i = 0;
	if (!*haystack && *needle)
		return (0);
	n_len = ft_strlen(needle);
	if (n_len == 0 || haystack == needle)
		return (hay_cpy);
	while (hay_cpy[i] != '\0' && i < len)
	{
		c = 0;
		while (hay_cpy[i + c] != '\0' && needle[c] != '\0'
			&& hay_cpy[i + c] == needle[c] && i + c < len)
			c++;
		if (c == n_len)
			return (hay_cpy + i);
		i++;
	}
	return (0);
}

// int	main(void)
// {
// 	char	*a;
// 	char	*b;

// 	a = "128493280";
// 	b = "280";
// 	a = ft_haystacknhaystack(a, b, 5);
// 	if (a == NULL)
// 	{
// 		printf("%s", "not there");
// 	}
// 	printf("%s", a);
// }
