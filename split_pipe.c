/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerraoui <aerraoui <marvin@42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 00:48:44 by aerraoui          #+#    #+#             */
/*   Updated: 2023/02/28 20:08:21 by aerraoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void cherchandrep(char **p)
{
	int i;
	int j;

	i = 0;

	while (p && p[i])
	{
		j = 0;
		while (p[i] && p[i][j])
		{
			if (p[i][j] == -1)
				p[i][j] = '|';
			j++;
		}
		i++;
	}
}

void fun(char *buff, char X)
{
	int i;
	i = 0;
	while (buff && buff[i])
	{
		if (buff[i] == X)
		{
			i++;
			while (buff && buff[i] != '\0' && buff[i] != X)
			{
				if (buff[i] == '|')
					buff[i] = -1;
				i++;
			}
		}
		i++;
	}
}

char *fuun_dgout(char *p)
{
	int i;
	int c;
	char *s;

	i = 0;
	c = 0;
	while (p && p[i])
	{
		if (p[i] == '"' && p[i + 1] && p[i + 1] == '"')
		{
			if (!(i != 0 && p[i - 1] == 39))
			{
				p[i++] = -2;
				p[i++] = -2;
				c += 2;
			}
			else
				i++;
		}
		else
			i++;
	}
	i = 0;

	s = malloc((ft_strlen(p) - c) + 1);
	c = 0;
	while (p && p[i])
	{
		if (p[i] != -2)
			s[c++] = p[i++];
		else
			i++;
	}
	s[c] = '\0';
	free(p);
	return (s);
}

char *fuun_sgout(char *p)
{
	int i;
	int c;
	char *s;

	i = 0;
	c = 0;
	while (p && p[i])
	{
		if (p[i] == 39 && p[i + 1] && p[i + 1] == 39)
		{
			if (!(i != 0 && p[i - 1] == '"'))
			{
				p[i++] = -2;
				p[i++] = -2;
				c += 2;
			}
			else
				i++;
		}
		else
			i++;
	}
	i = 0;

	s = malloc((ft_strlen(p) - c) + 1);
	c = 0;
	while (p && p[i])
	{
		if (p[i] != -2)
			s[c++] = p[i++];
		else
			i++;
	}
	s[c] = '\0';
	free(p);
	return (s);
}

char **split_pipe(char *buff)
{
	char **p;
	p = ft_split(buff, '|');
	//cherchandrep(p);
	return (p);
}
