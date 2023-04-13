/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallaoui <mallaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 18:09:40 by mallaoui          #+#    #+#             */
/*   Updated: 2023/04/13 18:11:07 by mallaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	delete_file_norm(int *size, int *i, int *x)
{
	(*x)++;
	while ((*x) != ((*size) + (*i)))
		(*x)++;
}

char	*delete_file(t_all1 **all, t_file1 *file, int i)
{
	int		size;
	char	*p;
	int		j;
	int		x;

	if (file->type == HER)
		size = ft_strlen(file->limiter) + 2;
	else
		size = ft_strlen(file->file) + 2;
	if (file->type == APP || file->type == HER)
		size++;
	p = malloc(ft_strlen((*all)->cmd));
	j = 0;
	x = 0;
	while ((*all)->cmd && (*all)->cmd[x] != '\0')
	{
		if (x == i - 1 || x == i)
			delete_file_norm(&size, &i, &x);
		else
			p[j++] = (*all)->cmd[x++];
	}
	p[j] = '\0';
	free((*all)->cmd);
	return (p);
}
