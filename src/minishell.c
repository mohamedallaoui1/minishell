/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell->c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallaoui <mallaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 00:49:53 by aerraoui          #+#    #+#             */
/*   Updated: 2023/04/13 18:50:32 by mallaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void	initialize(t_all1 **all)
{
	(*all)->cmd = NULL;
	(*all)->file = NULL;
	(*all)->next = NULL;
}


void	handle(int signum)
{
	(void)signum;
	glob.exit_status = 1;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	handle_1(int signum)
{
	(void)signum;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
}

void	handle_2(int signum)
{
	(void)signum;
	write(1, "Quit: 3\n", 9);
	rl_replace_line("", 0);
	rl_on_new_line();
}

void	free_struct(t_all1 **all)
{
	printf("the cmd is %p\n", (*all)->cmd);
	exit(0);
	if ((*all)->cmd)
		free((*all)->cmd);
	if ((*all)->file)
	{
		if ((*all)->file->file)
			free((*all)->file->file);
		if ((*all)->file->limiter)
			free((*all)->file->limiter);
		free((*all)->file);
	}
	free((*all));
}

char	*delet_speace(char *p)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	new = ft_calloc(ft_strlen(p) + 1, 1);
	while (p[i])
	{
		if (p[i] >= 8 && p[i] < 32)
		{
			new[j++] = 32;
			i++;
		}
		else
			new[j++] = p[i++];
	}
	new[j] = '\0';
	free(p);
	return (new);
}

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

void	reinitialize(t_everything **shell)
{
	(*shell)->all = NULL;
	(*shell)->file = NULL;
	(*shell)->vars = NULL;
	(*shell)->all = malloc(sizeof(t_all1));
	(*shell)->file = malloc(sizeof(t_file1));
	(*shell)->vars = malloc(sizeof(t_exec));
	initialize(&(*shell)->all);
}

void	free_everything_shell(t_everything **shell)
{
	free((*shell)->buffer);
	free((*shell)->vars);
	free((*shell)->all);
	free((*shell)->file);
}

void	get_attr(void)
{
	tcgetattr(STDIN_FILENO, &glob.old_attr);
	tcgetattr(STDIN_FILENO, &glob.new_attr);
	tcgetattr(STDIN_FILENO, &glob.reset_attr);
	glob.old_attr.c_lflag &= ~(ECHOCTL);
}

int	main(void)
{
	t_everything *shell;

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
		shell->buffer = fix_buffer_v2(shell->buffer);
		if (shell->buffer && ft_cmp(shell->buffer, "\0") != 0)
			pars_and_execute(&shell);
		free_everything_shell(&shell);
	}
}
