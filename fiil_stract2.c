/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fiil_stract2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallaoui <mallaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 23:23:23 by aerraoui          #+#    #+#             */
/*   Updated: 2023/03/11 18:32:15 by mallaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int     ft_tablen(char **p)
{
    int i;

    i = 0;
    while (p[i])
        i++;
    return (i);
}
void find_token(t_all1 **all,t_file1 **file ,int i)
{
    (*file)->append = 0;
    if((*all)->cmd[i] == '<')
    {
        if((*all)->cmd[i+1]== '<')
        {
            (*file)->type = HER;
            i++;
        }
        else
            (*file)->type = INF;
    }
    else
    {
        if ((*all)->cmd[i+1]== '>')
        {
            (*file)->append = 1;
            i++;
        }
        else
            (*file)->append = 0;
        (*file)->type = OUT ;
    }

}
void find_file(t_all1 **all,t_file1 **file,int i)
{
    char **p;

    if((*file)->type == HER || (*file)->append == 1)
        i++;
    p=ft_split((*all)->cmd + i ,' ');
    (*file)->file = ft_strdup(p[1]);
    ft_free(p);
}

char *delete_file(t_all1 **all,t_file1 *file ,int i)
{
    int size;
    char *p;
    int j;
    int x ;
    size = ft_strlen(file->file) + 2 ;
    if(file->append == 1 || file->type == HER)
        size++;
    p =malloc(ft_strlen((*all)->cmd));
    j =0;
    x =0;
    while((*all)->cmd && (*all)->cmd[x] != '\0')
    {
        if( x == i )
        {
            x++;
            while(x != (size + i))
                x++;
        }          
        else
        {
            p[j] = (*all)->cmd[x];
            j++;
            x++;
        }
    }
    p[j]='\0';
    free((*all)->cmd);
    return(p);
}

void file_filepro(t_file1 **file, t_all1 **all, int i)
{
    t_file1 *new;
    t_file1 *tmp;

    new = malloc(sizeof(t_file));
    if (!new)
        return;
    find_token(all,&new,i);
    find_file(all, &new,i);
    (*all)->cmd = delete_file(all,new,i);
    new->next = NULL;
    if (!*file)
        *file = new;
    else
    {
        tmp = *file;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = new;
    }
}

void    fill_struct2(char **p, t_all1 **all)
{
    int  i;
    int  j;
    int pross;
    int size;
    char type;
    t_all1 *tmp;
    size = ft_tablen(p);
    tmp= *all;
    i = 0;
    j =0;
    pross = 0;
    while (size)
    {
        tmp->next = malloc(sizeof(t_all1));
        tmp = tmp->next;
        tmp->next = NULL;
        size--;
    }
    tmp = *all;
    while(p[i])
    {
        tmp->cmd = ft_strdup(p[i]);
        tmp->file = NULL;
        while(tmp->cmd && tmp->cmd[j])
        {
            if(tmp->cmd[j]== '"' || tmp->cmd[j] == '\'')
            {
                type = tmp->cmd[j];
                    j++;
                while(tmp->cmd[j] != type)
                    j++;
                    j++;
            }
            else if(tmp->cmd[j] == '<' || tmp->cmd[j] == '>')
            {
                file_filepro(&tmp->file,&tmp,j);
                j = 0;
            }
            else 
                j++;
        }
        i++;
        tmp =tmp->next;
    }
}

