/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallaoui <mallaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 18:05:25 by mallaoui          #+#    #+#             */
/*   Updated: 2023/04/13 18:27:13 by mallaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_tablen(char **p)
{
	int	i;

	i = 0;
	while (p[i])
		i++;
	return (i);
}

void	find_token(t_all1 **all, t_file1 **file, int i)
{
	if ((*all)->cmd[i] == '<')
	{
		if ((*all)->cmd[i + 1] == '<')
		{
			(*file)->type = HER;
			i++;
		}
		else
			(*file)->type = INF;
	}
	else
	{
		if ((*all)->cmd[i + 1] == '>')
		{
			(*file)->type = APP;
			i++;
		}
		else
			(*file)->type = OUT ;
	}
}

char	*heredoc_name(int i)
{
	char	**which_tty;
	char	*name;
	char	*proccess_num;
	char	*final_name;
	char	*tmp;

	name = ft_strdup("_here_doc_");
	proccess_num = ft_itoa(i);
	which_tty = ft_split(ttyname(0), '/');
	tmp = ft_strjoin(proccess_num, name);
	final_name = ft_strjoin(tmp, which_tty[1]);
	tmp = ft_join("/tmp/", final_name);
	free(final_name);
	ft_free(which_tty);
	return (free(name), tmp);
}

void	find_file(t_all1 **all, t_file1 **file, int i, int j)
{
	char	**p;

	if ((*file)->type == HER || (*file)->type == APP)
		i++;
	p = ft_split((*all)->cmd + i, ' ');
	if ((*file)->type == HER)
	{
		if (!p[1])
			(*file)->limiter = NULL;
		else
			(*file)->limiter = ft_strdup(p[1]);
		(*file)->file = heredoc_name(j);
	}
	else
	{
		if (!p[1])
			(*file)->file = NULL;
		else
			(*file)->file = ft_strdup(p[1]);
	}
	ft_free(p);
}
