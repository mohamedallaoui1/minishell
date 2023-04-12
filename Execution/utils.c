/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallaoui <mallaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 01:30:16 by mallaoui          #+#    #+#             */
/*   Updated: 2023/04/12 00:51:20 by mallaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_paths(t_exec *vars)
{
	vars->i = 0;
    t_list *tmp = vars->env;
	while (tmp)
	{
		if (ft_cmp(tmp->name, "PATH") == 0)
			vars->splited = ft_split(tmp->cont, ':');
		tmp = tmp->next;
	}
}

char **list_to_double(t_list *env)
{
	int i = 0;
    t_list *tmp = env;
	char	**new;

    new = NULL;
	new = malloc (ft_lstsize(tmp) * sizeof (char *));
	while (tmp)
	{
		new[i] = ft_strdup(tmp->content);
		i++;
		tmp = tmp->next;
	}
    new[i] = NULL;
	return (new);
}

void destroy_qoute(char **p)
{
	int i;

	i = 0;
	
	while(p && p[i])
	{
		p[i]=delete_qouats(p[i]);
		i++;
	}
}

void    join_and_check_if_excutable(t_exec *vars, t_all1 *all)
{
    char    *tmp;
    char    **p;

    glob.exit_status = 0;
    p = NULL;
    p = ft_split(all->cmd, ' ');
    if (is_built_in(p[0]))
        check_built_ins(vars->duppin->outfile, 1, p, vars);
    else
       free(p);
    get_paths(vars);
    vars->i = 0;
    vars->full_cmd = ft_split(all->cmd, ' ');
    destroy_qoute(vars->full_cmd);
    if (vars->full_cmd[0])
    {
        vars->double_env = list_to_double(vars->env);
        if (vars->duppin->infile != 0)
            close(vars->duppin->infile);
        if (vars->duppin->outfile != 1)
        	close(vars->duppin->outfile);
        if (ft_strchr_normal(vars->full_cmd[0], '/') && access(vars->full_cmd[0], X_OK) == 0)
                execve(vars->full_cmd[0], vars->full_cmd, vars->double_env);
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
        if (!vars->splited && access(vars->full_cmd[0], X_OK) == 0)
                execve(vars->full_cmd[0], vars->full_cmd, vars->double_env);
        ft_printf(2, "bash: %s: command not found\n", vars->full_cmd[0]);
        glob.exit_status = 127;
        exit(glob.exit_status);
    }
}