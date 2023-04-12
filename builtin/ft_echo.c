/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallaoui <mallaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 23:49:00 by aerraoui          #+#    #+#             */
/*   Updated: 2023/04/10 04:05:14 by mallaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_echo2(int fd, char **p, int flag)
{
	int	i;
	int	savei;

	i = 1;
	savei = i;
	while (p[i])
	{
		if (ft_cmp(p[i], "-n") == 0)
		{
			i++;
			flag = 1;
			savei = i;
		}
		else
		{
			while (p[i])
			{
				if (savei == i)
					ft_printf(fd, "%s", p[i++]);
				else
					ft_printf(fd, " %s", p[i++]);
			}
		}
	}
	return (flag);
}

int	ft_echo(int fd, int check, char **p, t_list *env)
{
	int	i;
	int	flag;
	int	savei;

	i = 1;
	savei = i ;
	flag = 0;
	flag = ft_echo2(fd, p, flag);
	glob.exit_status = 0;
	if (flag == 0)
		ft_printf(fd, "\n");
	if (check)
		exit(glob.exit_status);
	return (ft_free(p), 0);
}
