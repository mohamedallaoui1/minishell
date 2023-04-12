/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerraoui <aerraoui <marvin@42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 14:14:08 by aerraoui          #+#    #+#             */
/*   Updated: 2023/03/29 23:10:55 by aerraoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	check(char c)
{
	char	*p;
	int		i;

	i = 0 ;
	p = "cspdiuxX%";
	while (p[i])
	{
		if (p[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	ft_put(int fd ,va_list p, char c)
{
	int	k ;

	k = 0;
	if ((c == 'i' || c == 'd'))
		k = ft_putnbr(fd, va_arg(p, int));
	else if (c == 'c')
	k = ft_putchar(fd, va_arg(p, int));
	else if (c == 's')
		k = ft_putstr(fd, va_arg(p, char *));
	else if (c == 'p')
		k = ft_putadd(fd, va_arg(p, void *));
	else if (c == 'x' || c == 'X')
		k = ft_puthexa(fd, va_arg(p, unsigned int), c);
	else if (c == 'u')
	k = ft_putuns(fd, va_arg(p, unsigned int));
	else if (c == '%')
	{
		write(fd, "%", 1);
		k++;
	}
	return (k);
}

int	ft_printf(int fd, const char *c, ...)
{	
	int			i;
	int			count;
	va_list		p;

	va_start(p, c);
	i = 0 ;
	count = 0;
	while (c[i])
	{
		if (c[i] == '%')
		{
			i++;
			if (check(c[i]))
			count += ft_put(fd, p, c[i++]);
		}
		else
		{
			write (fd, &c[i], 1);
			count++;
			i++;
		}
	} 
	va_end(p);
	return (count);
}
