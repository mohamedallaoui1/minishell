/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_wild.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallaoui <mallaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 22:18:44 by aerraoui          #+#    #+#             */
/*   Updated: 2023/04/13 21:22:29 by mallaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	if_find(char *p, char c)
{
	int	i;

	i = 0;
	while (p && p[i])
	{
		if (p[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	ft_rechname(char *haystack, char *needle)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	while (haystack[i])
	{
		while (haystack[i + j] == needle[j] && haystack[i + j] != '\0')
			j++;
		if (needle[j] == '\0')
			return (i + j);
		i++;
		j = 0;
	}
	return (-1);
}

int	check_wild_norm(char *card, char *file, char **p, int *arr)
{
	int	i;
	int	j;
	int	savej;

	savej = 0;
	i = arr[0];
	j = arr[1];
	while (p && p[i])
	{
		j = ft_rechname(file + savej, p[i]);
		savej += j;
		i++;
		if (j == -1)
			return (ft_free(p), -1);
	}
	if (card[ft_strlen(card) - 1] != '*')
	{
		if (ft_strncmp(file + (ft_strlen(file) - \
		ft_strlen(p[i - 1])), p[i - 1], ft_strlen(p[i - 1])))
			return (ft_free(p), -1);
		i++;
	}
	if (card[0] == '*' && if_find(card, '.') && ft_strncmp(file, ".", 1) == 0)
		return (ft_free(p), -1);
	return (0);
}

int	check_wild(char *card, char *file)
{
	char	**p;
	int		i;
	int		j;
	int		arr[2];

	i = 0;
	j = 0;
	p = ft_split(card, '*');
	if (ft_strlen(card) == 1 && ft_strncmp(file, ".", 1) != 0)
		return (ft_free(p), 1);
	else if (ft_strlen(card) == 1)
		return (-1);
	if (card[0] != '*')
	{
		if (ft_strncmp(file, p[0], ft_strlen(p[0])))
			return (ft_free(p), -1);
	}
	arr[0] = i;
	arr[1] = j;
	if (check_wild_norm(card, file, p, arr) == -1)
		return (-1);
	return (ft_free(p), 1);
}
