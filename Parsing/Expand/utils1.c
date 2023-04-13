/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallaoui <mallaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 09:54:07 by mallaoui          #+#    #+#             */
/*   Updated: 2023/04/13 17:11:39 by mallaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	fill_content(char **new, char *cont, int *i)
{
	int	j;

	j = 0;
	if (cont)
	{
		while (cont[j])
			(*new)[(*i)++] = cont[j++];
	}
}

int	norm_1(char *p, int *i, int *cont_size)
{
	char	*tmp;
	int		k;

	k = 0;
	tmp = NULL;
	if (p[(*i) + 1] == '$')
	{
		k = 1;
		(*cont_size)++;
		(*i)++;
	}
	else if (p[(*i) + 1] == '?')
	{
		k = 1;
		tmp = ft_itoa((long)glob.exit_status);
		(*cont_size) += ft_strlen(tmp);
		(*i) += 2;
		free(tmp);
	}
	return (k);
}

int	norm_2(char *p, int *i, int *cont_size, t_list *env)
{
	char	*s;
	char	*content;
	int		k;

	s = NULL;
	content = NULL;
	k = 0;
	if (ft_isalnum(p[(*i) + 1]))
	{
		k = 1;
		(*i)++;
		s = ft_strdupx(ft_firstword(&p[(*i)]));
		content = get_content(env, s);
		(*cont_size) += ft_strlen(content);
		(*i) += ft_strlen(s);
		free(s);
		free(content);
	}
	else
	{
		k = 1;
		(*cont_size)++;
		(*i)++;
	}
	return (k);
}

void	norm_count_total_1(char *p, int	*i, int	*cont_size, t_list *env)
{
	if (p[(*i)] == '$')
	{
		if (norm_1(p, i, cont_size))
			;
		else if (norm_2(p, i, cont_size, env))
			;
	}
	else
	{
		(*cont_size)++;
		(*i)++;
	}
}

void	count_total_while(char *p, int *i, int *cont_size, t_list *env)
{
	if (p[(*i)] == '\'')
	{
		(*i)++;
		while (p[(*i)] && p[(*i)] != '\'')
		{
			(*i)++;
			(*cont_size)++;
		}
		(*i)++;
		(*cont_size) += 2;
	}
	else if (p[(*i)] == '"')
	{
		(*i)++;
		while (p[(*i)] && p[(*i)] != '\"')
			norm_count_total_1(p, i, cont_size, env);
		(*i)++;
		(*cont_size) += 2;
	}
	else
		norm_count_total_1(p, i, cont_size, env);
}
