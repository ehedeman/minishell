/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehedeman <ehedeman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 11:49:40 by ehedeman          #+#    #+#             */
/*   Updated: 2024/01/19 12:15:34 by ehedeman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 10
#endif

char	*readline(int fd, char *str)
{
	char	*buff;
	int		bytes;

	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (0);
	bytes = 1;
	while (bytes != 0 && !ft_strchr_get(str, '\n'))
	{
		bytes = read(fd, buff, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[bytes] = '\0';
		str = ft_strjoin_get(str, buff);
	}
	free(buff);
	return (str);
}

char	*cut_line(char *str)
{
	char	*s;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i] != '\n' && str[i])
		i++;
	if (!str[i])
	{
		free(str);
		return (0);
	}
	s = malloc(sizeof(char) * (ft_strlen(str) - i + 1));
	if (!s)
		return (0);
	i++;
	while (str[i])
		s[j++] = str[i++];
	s[j] = '\0';
	free(str);
	return (s);
}

char	*get_next_line(int fd)
{
	static char		*str[4096];
	char			*ret;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	str[fd] = readline(fd, str[fd]);
	if (!str[fd])
		return (NULL);
	ret = copy_line(str[fd]);
	str[fd] = cut_line(str[fd]);
	return (ret);
}
//int	main(int argc, char **argv)
//{
//	char	*a;
//	int		i;
//	int		b;
//
//	
//	if (argc != 3)
//	{
//		printf("No input");
//		return (0);
//	}
//	b = atoi(argv[2]);
//	a = argv[1];
//	i = open(argv[1], O_RDONLY);
//	while (b)
//	{
//		a = get_next_line(i);
//		printf("%s", a);
//		free(a);
//		b--;
//	}
//	printf("\n\n");
//	return (0);
//}
