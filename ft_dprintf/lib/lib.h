/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerraoui <aerraoui <marvin@42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 00:30:12 by aerraoui          #+#    #+#             */
/*   Updated: 2023/03/30 00:38:29 by aerraoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef  LIB_H
# define LIB_H

# include <stdio.h>
# include<stdlib.h>
# include<unistd.h>
# include <fcntl.h>
# include<strings.h>
# include<limits.h>
# include<stdarg.h>

char	*ft_itoa(long a);
int		ft_strlen1(const char *str);
int		ft_putstr(int fd, char *s);
int		ft_putnbr(int fd, int a);
int		ft_putchar(int fd, char c);
int		ft_puthexa(int fd, unsigned int a, char c);
int		ft_putadd(int fd, void *p);
int		ft_putuns(int fd, unsigned int a);

#endif