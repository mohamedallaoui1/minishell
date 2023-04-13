/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerraoui <aerraoui <marvin@42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 12:16:09 by aerraoui          #+#    #+#             */
/*   Updated: 2023/04/12 23:17:05 by aerraoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(int fd, int check, char **p, t_list *env)
{
	if (p[1])
	{
		ft_printf(2, "env: %s: No such file or directory\n", p[1]);
		glob.exit_status = 127;
		if (check)
			exit (glob.exit_status);
		else
			return (ft_free(p), 0);
	}
	while (env)
	{
		if (env->cont)
			ft_printf(fd, "%s\n", env->content);
		env = env->next;
	}
	if (check)
		exit(glob.exit_status);
	else
		return (ft_free(p), 0);
}
