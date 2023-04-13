/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallaoui <mallaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 00:49:53 by aerraoui          #+#    #+#             */
/*   Updated: 2023/04/13 23:31:05 by mallaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pars_and_execute(t_everything **shell)
{
	if (ft_eroro((*shell)->buffer))
	{
		(*shell)->buffer = delet_speace((*shell)->buffer);
		(*shell)->p = ft_split((*shell)->buffer, '|');
		fill_struct2((*shell)->p, &(*shell)->all);
		(*shell)->tmp = (*shell)->all;
		ft_free((*shell)->p);
		if ((*shell)->all)
			open_here_doc(&(*shell)->all, (*shell)->env);
		while ((*shell)->all)
		{
			(*shell)->all->cmd = expand((*shell)->env, (*shell)->all->cmd);
			(*shell)->all->cmd = ft_wildcard((*shell)->all->cmd);
			(*shell)->all = (*shell)->all->next;
		}
		(*shell)->all = (*shell)->tmp;
		if (glob.check_sig == 0)
		{
			execution((*shell)->tmp, &(*shell)->vars, (*shell)->env);
			dup2((*shell)->vars->in, 0);
			dup2((*shell)->vars->out, 1);
			(close((*shell)->vars->in), close((*shell)->vars->out));
		}
		free_all(&(*shell)->all);
	}
}

int	main(void)
{
	t_everything	*shell;

	shell = NULL;
	shell = malloc(sizeof(t_everything));
	shell->env = NULL;
	fill_env(&shell->env);
	get_attr();
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		glob.check_sig = 0;
		tcsetattr(STDIN_FILENO, TCSANOW, &glob.old_attr);
		(reinitialize(&shell), signal(SIGINT, handle), shell->buff = \
		readline("minishell> "), signal(SIGINT, SIG_IGN));
		if (!shell->buff)
			(tcsetattr(STDIN_FILENO, TCSANOW, &glob.reset_attr), \
			ft_printf(2, "exit\n"), exit(glob.exit_status));
		(add_history(shell->buff), shell->buffer = \
		ft_strdup(shell->buff), free(shell->buff));
		shell->buffer = fix_buffer(shell->buffer);
		if (shell->buffer && ft_cmp(shell->buffer, "\0") != 0)
			pars_and_execute(&shell);
		free_everything_shell(&shell);
	}
}
