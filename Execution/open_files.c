/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallaoui <mallaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 07:51:44 by mallaoui          #+#    #+#             */
/*   Updated: 2023/04/13 07:52:11 by mallaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	open_her_file(t_exec *vars, t_file1 *tmp, int check)
{
	if (tmp->type == HER)
	{
		vars->duppin->infile = open(tmp->file, O_RDONLY);
		if (vars->duppin->infile < 0)
		{
			perror("Error");
			if (check)
			{
				glob.exit_status = 1;
				exit(glob.exit_status);
			}
			else
				return (1);
		}
	}
	return (0);
}

int	open_in_file(t_exec *vars, t_file1 *tmp, int check)
{
	if (tmp->type == INF)
	{
		vars->duppin->infile = open(tmp->file, O_RDONLY);
		if (vars->duppin->infile < 0)
		{
			perror("Error");
			if (check)
			{
				glob.exit_status = 1;
				exit(glob.exit_status);
			}
			else
				return (1);
		}
	}
	if (open_her_file(vars, tmp, check))
		return (1);
	return (0);
}

int	open_out_file(t_exec *vars, t_file1 *tmp, int check)
{
	if (tmp->type == OUT || tmp->type == APP)
	{
		if (tmp->type == APP)
			vars->duppin->outfile = open(tmp->file, \
			O_RDWR | O_CREAT | O_APPEND, 0644);
		else
			vars->duppin->outfile = open(tmp->file, \
			O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (vars->duppin->outfile < 0)
		{
			perror("Error");
			if (check)
			{
				glob.exit_status = 1;
				exit(glob.exit_status);
			}
			else
				return (1);
		}
	}
	return (0);
}

int	open_files(t_exec **vars, t_file1 *file, int check)
{
	t_file1	*tmp;
	char	*gg;
	char	**cc;

	tmp = file;
	while (tmp)
	{
		gg = ft_strdup1(tmp->file);
		tmp->file = ft_wildcard(tmp->file);
		cc = ft_split(tmp->file, ' ');
		if ((ft_strchr_normal(gg, '*') && ft_tablen(cc) > 1) \
		|| !check_ambiguous(&tmp, (*vars)->env))
			(ft_printf(2, "bash: %s: ambiguous redirect\n", gg), \
			glob.exit_status = 1, ft_free(cc), exit(glob.exit_status));
		else if (open_in_file(*vars, tmp, check))
			return (1);
		else if (open_out_file(*vars, tmp, check))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
