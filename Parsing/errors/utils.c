/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallaoui <mallaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 01:00:03 by mallaoui          #+#    #+#             */
/*   Updated: 2023/04/14 01:00:33 by mallaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	syntaxeror(char *p)
{
	int		i;
	char	type;

	i = 0;
	while (p && p[i])
	{
		if (p[i]== '\'' || p[i] == '"')
		{
			type = p[i];
			i++;
			while (p[i] && p[i] !=type)
				i++;
				i++;
		}
		else if (p[i] == ';' || p[i] == '\\')
		{
			ft_printf(2, "syntax error\n");
			return (-1);
		}
		else
			i++;
	}
	return (1);
}

int	ft_erorr(char *buff, char bu, int i)
{
	if (bu == '|')
	{
		i++;
		while (buff[i] && buff[i] == ' ')
			i++;
		if (buff[i] == '|')
			return (-1);
		return (i);
	}
	else
	{
		i++;
		while (buff[i] && buff[i] != bu)
			i++;
		return (i);
	}
}

int	check_error_nrm(char *buff, int i)
{
	while (buff[i])
	{
		if (buff[i] == '|' || buff[i] == '"' || buff[i] == '\'')
		{
			i = ft_erorr(buff, buff[i], i);
			if (i == -1)
			{
				printf("bash: syntax error near unexpected token `|'\n");
				return (0);
			}
		}
		else
			i++;
	}
	return (1);
}

int	ft_check_erorr(char *buff)
{
	char	*s;
	int		i;

	i = 0;
	s = ft_firstword(buff);
	if (s && s[0] == '|')
	{
		printf("bash: syntax error near unexpected token `|'\n");
		free(s);
		return (0);
	}
	if (check_error_nrm(buff, 0) == 0)
		return (0);
	i = 0;
	while (buff[i])
		i++;
	i--;
	while (buff[i] == ' ')
		i--;
	if (buff[i] == '|')
	{
		printf("bash: syntax error near unexpected token `|'\n");
		return (0);
	}
	return (free(s), 1);
}

int check_token_norm(char *buff, int *i)
{
	if (buff[(*i)] == '<')
	{
		if (buff[++(*i)] == '<')
		{
			(*i)++;
			while (buff[(*i)] == ' ')
					(*i)++;
			if (buff[(*i)] == '<' || buff[(*i)] == '>')
				return (0);
		}
		else
		{
			if (buff[(*i)] == '>')
				return (0);
			while (buff[(*i)] && buff[(*i)] == ' ')
				(*i)++;
			if (buff[(*i)] == '<' || buff[(*i)] == '>')
				return (0);
		}
	}
	return (1);
}