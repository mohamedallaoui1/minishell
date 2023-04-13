/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallaoui <mallaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 23:49:00 by aerraoui          #+#    #+#             */
/*   Updated: 2023/04/13 08:19:14 by mallaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int flagchechker(char *p)
{
	int i;
	
	i = 2;
	while(p && p[i] && p[i] != ' ')
	{
		if(p[i] != 'n')
			return(0);
		i++;
	}
	return (1);
}


int	ft_echo2(int fd, char **p, int flag)
{
	int	i;
	int	savei;

	i = 1;
	savei = i;
	while (p[i])
	{
		if (!ft_strncmp(p[i], "-n",2) && flagchechker(p[i]))
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

	(void)env;
	i = 1;
	savei = i ;
	flag = 0;
	flag = ft_echo2(fd, p, flag);
	if (flag == 0)
		ft_printf(fd, "\n");
	if (check)
		exit(glob.exit_status);
	glob.exit_status = 0;
	return (ft_free(p), 0);
}
