/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallaoui <mallaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 07:27:10 by mallaoui          #+#    #+#             */
/*   Updated: 2023/04/13 08:27:30 by mallaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	first(t_exec **vars, t_all1 *all)
{
	t_exec	*tmp;

	tmp = *vars;
	close(tmp->fd[0]);
	if (tmp->duppin->infile != 0)
		dup2(tmp->duppin->infile, 0);
	else
		dup2(tmp->in, 0);
	if (tmp->duppin->outfile != 1)
		dup2(tmp->duppin->outfile, 1);
	else if (all->next != NULL)
		dup2(tmp->fd[1], 1);
	else
	{
		dup2(tmp->out, 1);
		close(tmp->fd[1]);
	}
	join_and_check_if_excutable(tmp, all);
}

void	last(t_exec **vars, t_all1 *all)
{
	t_exec	*tmp;

	tmp = *vars;
	close(tmp->fd[1]);
	close(tmp->in);
	if (tmp->duppin->infile != 0)
		dup2(tmp->duppin->infile, 0);
	if (tmp->duppin->outfile != 1)
		dup2(tmp->duppin->outfile, 1);
	join_and_check_if_excutable(tmp, all);
}

void	middle(t_exec **vars, t_all1 *all)
{
	t_exec	*tmp;

	tmp = *vars;
	close(tmp->in);
	close(tmp->out);
	close(tmp->fd[0]);
	if (tmp->duppin->infile != 0)
		dup2(tmp->duppin->infile, 0);
	if (tmp->duppin->outfile != 1)
		dup2(tmp->duppin->outfile, 1);
	else
		dup2(tmp->fd[1], 1);
	join_and_check_if_excutable(tmp, all);
}

void	execute(t_exec **vars, t_all1 *all)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &glob.new_attr);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	open_files(vars, all->file, 1);
	if (all->cmd[0] == 0 || only_white_spaces(all->cmd))
		exit(glob.exit_status);
	if (all->index == 0)
		first(vars, all);
	else if (all->next == NULL && all->index != 0)
		last(vars, all);
	else
		middle(vars, all);
}
