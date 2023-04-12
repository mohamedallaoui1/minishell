/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerraoui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 16:13:31 by aerraoui          #+#    #+#             */
/*   Updated: 2022/11/24 16:13:13 by aerraoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t		i;
	char		*p;
	size_t		j ;
	size_t		lens1;

	if (!s1 && s2)
		return (ft_strdup1(s2));
	if (!s1 && !s2)
		return (NULL);
	i = 0;
	j = 0;
	lens1 = ft_strlen(s1);
	p = malloc(lens1 + ft_strlen(s2)+ 1);
	if (!p)
		return (0);
	while (i < lens1)
	{
		p[i] = s1[i];
		i++;
	}
	while (i < lens1 + ft_strlen(s2))
		p[i++] = s2[j++];
	p[i] = '\0';
	return (free(s1), p);
}

char	*ft_strdup1(char *s1)
{
	char	*p;
	int		i ;
	int		size;

	if (!s1)
		return (NULL);
	size = ft_strlen(s1);
	i = 0;
	p = malloc(sizeof(char) * (size + 1));
	if (!p)
		return (0);
	else
	{
		while (i < size)
		{
			p[i] = s1[i];
			i++;
		}
		p[i] = '\0';
	}
	return (p);
}
