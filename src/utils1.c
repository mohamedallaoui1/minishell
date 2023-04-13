/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallaoui <mallaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 22:05:15 by mallaoui          #+#    #+#             */
/*   Updated: 2023/04/13 22:08:40 by mallaoui         ###   ########.fr       */
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
