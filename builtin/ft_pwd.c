/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerraoui <aerraoui <marvin@42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 15:16:12 by aerraoui          #+#    #+#             */
/*   Updated: 2023/04/05 14:26:24 by aerraoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

int ft_pwd(int fd,int check, char **p, t_list *env)
{
    char pwd[1024];
    
    (void)p;
    (void)env;
    getcwd(pwd, sizeof(pwd));
    ft_printf(fd, "%s\n", pwd);
    if (check)
       exit(0);
    else
       return (ft_free(p), 0);
}