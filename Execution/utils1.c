/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallaoui <mallaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 07:32:39 by mallaoui          #+#    #+#             */
/*   Updated: 2023/04/13 08:41:21 by mallaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_struct(t_exec **vars, t_list *env)
{
	int	i;

	i = 0;
	(*vars)->i = 0;
	(*vars)->path = NULL;
	(*vars)->splited = NULL;
	(*vars)->double_env = NULL;
	(*vars)->env = env;
	(*vars)->duppin = malloc(sizeof(t_dup));
	(*vars)->duppin->infile = 0;
	(*vars)->duppin->outfile = 1;
}

void	indexing(t_all1 **all)
{
	t_all1	*temp;
	int		i;

	temp = *all;
	i = 0;
	while (temp)
	{
		temp->index = i;
		i++;
		temp = temp->next;
	}
}

void	check_built_ins(int fd, int check, char **p, t_exec *vars)
{
	if (!ft_cmp(p[0], "unset"))
		ft_unset(fd, check, p, vars->env);
	else if (!ft_cmp(p[0], "cd"))
		ft_cd(fd, check, p, vars->env);
	else if (!ft_cmp(p[0], "env"))
		ft_env(fd, check, p, vars->env);
	else if (!ft_cmp(p[0], "export"))
		ft_export(fd, check, p, vars->env);
	else if (!ft_cmp(p[0], "exit"))
		ft_exit(fd, check, p, vars->env);
	else if (!ft_cmp(p[0], "pwd"))
		ft_pwd(fd, check, p, vars->env);
	else if (!ft_cmp(p[0], "echo"))
		ft_echo(fd, check, p, vars->env);
}

int	is_built_in(char *p)
{
	if (!ft_cmp(p, "unset"))
		return (1);
	else if (!ft_cmp(p, "cd"))
		return (1);
	else if (!ft_cmp(p, "env"))
		return (1);
	else if (!ft_cmp(p, "export"))
		return (1);
	else if (!ft_cmp(p, "exit"))
		return (1);
	else if (!ft_cmp(p, "pwd"))
		return (1);
	else if (!ft_cmp(p, "echo"))
		return (1);
	return (0);
}

int	only_white_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}
