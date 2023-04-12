/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putuns.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerraoui <aerraoui <marvin@42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 18:43:34 by aerraoui          #+#    #+#             */
/*   Updated: 2023/03/30 00:42:14 by aerraoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

int	ft_putuns(int fd, unsigned int a)
{
	char	*p;
	int		c;

	p = ft_itoa(a);
	c = ft_strlen1(p);
	write(fd, p, ft_strlen1(p));
	free(p);
	return (c);
}
