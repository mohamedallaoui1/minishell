/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallaoui <mallaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 01:01:07 by mallaoui          #+#    #+#             */
/*   Updated: 2023/04/14 01:01:30 by mallaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_token1(char *buff)
{
	int		i;
	char	type;

	i = 0;
	while (buff[i])
	{
		if (buff[i] == '\'' || buff[i] == '"')
		{
			type = buff[i++];
			while (buff[i] && buff[i] != type)
			i++;
		}
		if (check_token_norm(buff, &i) == 0)
			return (0);
		i++;
	}
	return (1);
}

int check_token2_norm(char *buff, int *i)
{
	if (buff[(*i)] == '>' )
	{
		if (buff[++(*i)] == '>')
		{
			(*i)++;
			while (buff[(*i)] == ' ')
					(*i)++;
			if (buff[(*i)] == '<' || buff[(*i)] == '>')
				return (0);
		}
		else
		{
			if (buff[(*i)] == '<')
				return (0);
			while (buff[(*i)] && buff[(*i)] == ' ')
				(*i)++;
			if (buff[(*i)] == '<' || buff[(*i)] == '>')
				return (0);
		}
	}
	return (1);
}

int	k_token2(char *buff)
{
	int		i;
	char	type;

	i = 0;
	while (buff[i])
	{
		if (buff[i] == '\'' || buff[i] == '"')
		{
			type = buff[i++];
			while (buff[i] && buff[i] != type)
			i++;
		}
		if (check_token2_norm(buff, &i) == 0)
			return (0);
		i++;
	}
	return (1);
}

int	check_token0_norm(char *buff, int *i, int *j)
{
	char type;
	while (p[(*i)][(*j)])
	{
		if (p[(*i)][(*j)] == '<' || p[(*i)][(*j)] == '>')
		{
			if (!p[(*i)][(*j) + 1])
				return (ft_free(p), 0);
			type = p[(*i)][(*j)];
			(*j)++;
			if (p[i][j] == type)
				(*j)++;
			while (p[(*i)][(*j)] == ' ')
				(*j)++;
			if (!p[(*i)][(*j)])
				return (ft_free(p), 0);
		}
		(*j)++;
	}
	return (1);
}

int check_token0(char *buff)
{
	int		i;
	int		j;
	char	**p;

	i = 0;
	p = ft_split(buff, '|');
	while (p && p[i])
	{
		j = 0;
		if (check_token0_norm(buff, &i, &j) == 0)
			return (0);
		i++;
	}
	return (ft_free(p), 1);
}
