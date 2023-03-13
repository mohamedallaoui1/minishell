/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_firstword.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerraoui <aerraoui <marvin@42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 23:51:30 by aerraoui          #+#    #+#             */
/*   Updated: 2023/03/03 00:43:57 by aerraoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

char *ft_firstword(char *p)
{
    int i;
    char *s;
    int savei;
    int j ;
    
    
     i =0;
     j = 0;
    if(!p)
        return (NULL);
    while(p[i] && p[i] == ' ')
        i++;
    if (!p[i])
        return (NULL);
    savei=i+1;
    while(p[savei] && p[savei] != ' ' && ft_isalnum(p[savei]))
        savei++;
    s = malloc ((savei - i + 1 ) * 1 );
    while(p[i] && p[i] != ' ' && ft_isalnum(p[i]))
        s[j++] = p[i++];
    s[j]= '\0';
    return(s);
}
