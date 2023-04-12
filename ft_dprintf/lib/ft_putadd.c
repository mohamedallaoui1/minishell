/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerraoui <aerraoui <marvin@42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 13:33:42 by aerraoui          #+#    #+#             */
/*   Updated: 2023/03/29 23:03:59 by aerraoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

static void	ft_hexa(int fd, unsigned long a)
{
	char	*b;

	b = "0123456789abcdef";
	if (a < 16)
	{
		ft_putchar(fd,b[a]);
	}
	else
	{
		ft_hexa(fd, a / 16);
		ft_hexa(fd, a % 16);
	}
}

static int	ft_count(unsigned long a)
{
	unsigned long	c ;
	int				k;

	k = 0;
	c = a;
	if (c == 0)
		k++;
	while (c != 0)
	{
		c = c / 16;
		k++;
	}
	return (k);
}

int	ft_putadd(int fd,void *a)
{
	unsigned long	c;

	c = (unsigned long)a;
	write(1, "0x", 2);
	ft_hexa(fd,c);
	return (ft_count(c)+2);
}
