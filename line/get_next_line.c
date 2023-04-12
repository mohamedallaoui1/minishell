/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerraoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 16:11:14 by aerraoui          #+#    #+#             */
/*   Updated: 2022/11/24 21:45:45 by aerraoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"get_next_line.h"

char	*ft_strchr(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] == '\n' )
			return (s + i);
		i++;
	}
	return (0);
}

char	*ft_read(int fd, char *p)
{
	char	*buff;
	int		c;

	c = 1;
	buff = malloc((size_t)BUFFER_SIZE + 1);
	while (!ft_strchr(p) && c > 0)
	{
		c = read(fd, buff, BUFFER_SIZE);
		if (c == -1)
			return (free(buff), free(p), NULL);
		if (c == 0)
			return (free(buff), p);
		buff[c] = '\0';
		p = ft_strjoin(p, buff);
	}
	free(buff);
	return (p);
}

char	*retu_next_line(char *p)
{
	int		i ;
	char	*m;

	i = 0;
	if (!p)
		return (NULL);
	while (p[i] && p[i] != '\n')
		i++;
	if (p[i] == '\n')
		i++;
		m = malloc(i + 1);
	if (!m)
		return (NULL);
	i = 0;
	while (p[i] && p[i] != '\n' )
	{
		m[i] = p[i];
		i++;
	}
	if (p[i] == '\n')
		m[i++] = '\n';
	m[i] = '\0';
	return (m);
}

char	*ft_newsaver(char *saver)
{
	int		i;
	int		j;
	char	*p;

	if (!saver)
		return (NULL);
	i = 0;
	j = 0;
	while (saver[i] && saver[i] != '\n')
		i++;
	if (saver[i] == '\0' || saver[i + 1] == '\0')
		return (free(saver), NULL);
	i++;
	p = malloc(ft_strlen(saver) - i + 1);
	if (!p)
		return (NULL);
	while (saver[i])
		p[j++] = saver[i++];
	p[j] = '\0';
	free (saver);
	return (p);
}

char	*get_next_line(int fd)
{
	static char	*saver;
	char		*p;

	if (fd < 0 || fd > 10240 || BUFFER_SIZE <= 0)
		return (NULL);
	saver = ft_read(fd, saver);
	if (!saver)
		return (NULL);
	p = retu_next_line(saver);
	saver = ft_newsaver(saver);
	return (p);
}
