/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_stract2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallaoui <mallaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 23:23:23 by aerraoui          #+#    #+#             */
/*   Updated: 2023/04/13 18:24:35 by mallaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	file_filepro(t_file1 **file, t_all1 **all, int i, int j)
{
	t_file1	*new;
	t_file1	*tmp;

	new = malloc(sizeof(t_file1));
	if (!new)
		return ;
	new->file = NULL;
	new->type = 0;
	new->limiter = NULL;
	find_token(all, &new, i);
	find_file(all, &new, i, j);
	(*all)->cmd = delete_file(all, new, i);
	new->next = NULL;
	if (!*file)
		*file = new;
	else
	{
		tmp = *file;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	qoute_condition(t_all1 *tmp, int *i, char type)
{
	if (tmp->cmd[(*i)] == '"' || tmp->cmd[(*i)] == '\'')
	{
		type = tmp->cmd[(*i)];
			(*i)++;
		while (tmp->cmd[(*i)] != type)
			(*i)++;
			(*i)++;
	}
}

void	fill_stract2_norm(char **p, t_all1 *tmp, int *arr, char type)
{
	while (p[arr[0]])
	{
		arr[1] = 0;
		tmp->cmd = ft_strdup(p[arr[0]]);
		tmp->file = NULL;
		while (tmp->cmd && tmp->cmd[arr[1]])
		{
			qoute_condition(tmp, &arr[1], type);
			if (tmp->cmd[arr[1]] == '<' || tmp->cmd[arr[1]] == '>')
			{
				file_filepro(&tmp->file, &tmp, arr[1], arr[0]);
				arr[1] = 0;
			}
			else
				arr[1]++;
		}
		arr[0]++;
		tmp = tmp->next;
	}
}

void	fill_struct2(char **p, t_all1 **all)
{
	int		arr[2];
	int		size;
	char	type;
	t_all1	*tmp;

	if (!p)
		return ;
	size = ft_tablen(p);
	tmp = *all;
	tmp->next = NULL;
	arr[0] = 0;
	arr[1] = 0;
	type = 0;
	while (size - 1)
	{
		tmp->next = malloc(sizeof(t_all1));
		tmp = tmp->next;
		tmp->next = NULL;
		size--;
	}
	tmp = *all;
	fill_stract2_norm(p, tmp, arr, type);
}
