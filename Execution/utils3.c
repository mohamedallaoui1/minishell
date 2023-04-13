/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallaoui <mallaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 08:38:39 by mallaoui          #+#    #+#             */
/*   Updated: 2023/04/13 08:39:07 by mallaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	search_and_check(t_exec *vars)
{
	char	*tmp;

	tmp = NULL;
	while (vars->splited && vars->splited[vars->i])
	{
		if (vars->full_cmd[0][0] == '.' || vars->full_cmd[0][0] == '/')
			break ;
		tmp = ft_strjoin(vars->splited[vars->i], "/");
		vars->path = ft_strjoin(tmp, vars->full_cmd[0]);
		if (access(vars->path, X_OK) == 0)
			execve(vars->path, vars->full_cmd, vars->double_env);
		free(vars->path);
		vars->i++;
	}
}
