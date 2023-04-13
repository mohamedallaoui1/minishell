/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ambiguous.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerraoui <aerraoui <marvin@42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 21:21:53 by aerraoui          #+#    #+#             */
/*   Updated: 2023/04/13 02:06:19 by aerraoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int thechecker(char *p)
{
    int i ;
    
    i = 0;
    while(p[i])
    {
        if(p[i] =='"')
        {
            while(p[i] && p[i] != '"')
                i++;
        }
        else
        {
            if(p[i] == '$')
            {
                if(p[i + 1] && p[i+1] != '$')
                    return(1);
            }
        }
        i++;
    }
    return (0);
}
int clacul(char **p)
{
    int i;

    i = 0;
    while (p &&  p[i])
    {
        i++;
    }
    return(ft_free(p),i);
}

int check_ambiguous(t_file1 **file, t_list *env)
{
    t_file1 *tmp;
    char **p;
    
    tmp = *file;
    if(tmp->type != HER)
    {
        if(thechecker(tmp->file))
        {
            
            tmp->file =expand(env,tmp->file);
            
            p = ft_split(tmp->file,' ');
            if(clacul(p) != 1)
                return (0);
            else
            tmp->file = delete_qouats(tmp->file);
        }
        else
        {
            tmp->file =expand(env,tmp->file);
            tmp->file = delete_qouats(tmp->file);    
        }
        return(1);
    }
    else
        return(1);
}