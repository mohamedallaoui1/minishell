/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallaoui <mallaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 14:23:20 by mallaoui          #+#    #+#             */
/*   Updated: 2023/04/13 08:27:16 by mallaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_everything(t_exec *vars)
{
	if (vars->path)
		free(vars->path);
	if (vars->double_env)
		ft_free(vars->double_env);
	if (vars->duppin)
		free(vars->duppin);
	if (vars->splited)
		ft_free(vars->splited);
}

int	builtins(t_all1 *all, t_exec **vars)
{
	t_exec		*tmp;
	char		**p;

	tmp = *vars;
	p = NULL;
	p = ft_split(all->cmd, ' ');
	destroy_qoute(p);
	if (is_built_in(p[0]) && all->next == NULL)
	{
		open_files(vars, all->file, 0);
		check_built_ins(tmp->duppin->outfile, 0, p, (*vars));
		free_everything(tmp);
		return (1);
	}
	else
		ft_free(p);
	return (0);
}

void	parent_proccess(t_exec **vars)
{
	t_exec		*tmp;
	int			save;

	tmp = *vars;
	save = tmp->fd[0];
	dup2(save, 0);
	if (tmp->duppin->infile != 0)
		close(tmp->duppin->infile);
	if (tmp->duppin->outfile != 1)
		close(tmp->duppin->outfile);
	close(tmp->fd[0]);
	close(tmp->fd[1]);
	tcsetattr(STDIN_FILENO, TCSANOW, &glob.old_attr);
}

int	the_while(t_all1 *temp, t_exec **vars, t_exec *tmp)
{
	while (temp)
	{
		pipe(tmp->fd);
		tmp->duppin->infile = 0;
		tmp->duppin->outfile = 1;
		tmp->id = fork();
		if ((*vars)->id == 0)
			execute(vars, temp);
		else
		{
			signal(SIGINT, handle_1);
			signal(SIGQUIT, handle_2);
			parent_proccess(&tmp);
		}
		temp = temp->next;
	}
	return (tmp->id);
}

void	execution(t_all1 *all, t_exec **vars, t_list *env)
{
	t_exec		*tmp;
	t_all1		*temp;

	tmp = *vars;
	temp = all;
	init_struct(&tmp, env);
	indexing(&all);
	tmp->in = dup(0);
	tmp->out = dup(1);
	if (builtins(all, &tmp))
		return ;
	the_while(temp, &tmp, tmp);
	waitpid(tmp->id, &tmp->status, 0);
	if (WIFEXITED(tmp->status))
		glob.exit_status = WEXITSTATUS(tmp->status);
	if (WIFSIGNALED(tmp->status))
		glob.exit_status = WTERMSIG(tmp->status) + 128;
	while (wait(NULL) != -1)
		;
	free_everything(tmp);
}
