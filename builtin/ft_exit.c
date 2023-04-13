/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallaoui <mallaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 12:17:06 by aerraoui          #+#    #+#             */
/*   Updated: 2023/04/13 20:00:24 by mallaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	isnum(char *p)
{
	int	i;

	i = 0;
	while (p[i])
	{
		if (!ft_isdigit(p[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit2(int fd, int status, int check)
{
	ft_printf(fd, "exit\nbash: exit: too many arguments\n");
	status = 1;
	if (check)
		exit(status);
	return (status);
}

int	ft_exit(int fd, int check, char **p, t_list *env)
{
	(void)env;
	if (!p[1])
		exit(glob.exit_status);
	else
	{
		if (!isnum(p[1]))
		{
			ft_printf(fd, "exit\nbash: exit: hhh: numeric argument required\n");
			exit(255);
		}
		else if (p[2])
		{
			glob.exit_status = ft_exit2(fd, glob.exit_status, check);
			return (ft_free(p), 0);
		}
		else
		{
			ft_printf (fd, "exit");
			exit((unsigned char)ft_atoi(p[1]));
		}
	}
	if (check)
		exit(glob.exit_status);
	else
		return (ft_free(p), 0);
}
