/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fiil_stract2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallaoui <mallaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 23:23:23 by aerraoui          #+#    #+#             */
/*   Updated: 2023/04/09 23:42:17 by mallaoui         ###   ########.fr       */
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

void find_token(t_all1 **all, t_file1 **file, int i)
{
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
            (*file)->type = APP;
            i++;
        }
        else
            (*file)->type = OUT ;
    }

}

char *heredoc_name(int i)
{
    char **which_tty;
    char *name;
    char *proccess_num;
    char *final_name;
    char *tmp;

    name = ft_strdup("_here_doc_");
    proccess_num = ft_itoa(i);
    which_tty = ft_split(ttyname(0), '/');
    tmp = ft_strjoin(proccess_num, name);
    final_name = ft_strjoin(tmp, which_tty[1]);
    tmp = ft_join("/tmp/", final_name);
    free(final_name);
    ft_free(which_tty);
    return (free(name), tmp);
}

void find_file(t_all1 **all,t_file1 **file,int i, int j)
{
    char **p;

    if ((*file)->type == HER || (*file)->type == APP)
        i++;
    p = ft_split((*all)->cmd + i ,' ');
    if ((*file)->type == HER)
    {
        if(!p[1])
            (*file)->limiter = NULL;
        else
            (*file)->limiter = ft_strdup(p[1]);
        (*file)->file = heredoc_name(j);
    }
    else
    {
        if(!p[1])
            (*file)->file = NULL;
        else
            (*file)->file = ft_strdup(p[1]);
    }
    ft_free(p);
}



char *          delete_file(t_all1 **all,t_file1 *file ,int i)
{
    int size;
    char *p;
    int j;
    int x ;
    if(file->type == HER)
        size = ft_strlen(file->limiter) + 2 ;
    else
        size = ft_strlen(file->file) + 2 ;

    if(file->type == APP || file->type == HER)
        size++;
    p =malloc(ft_strlen((*all)->cmd));
    j =0;
    x =0;
    while((*all)->cmd && (*all)->cmd[x] != '\0')
    {
        if( x == i-1 || x == i )
        {
            x++;
            while(x != (size + i ))
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

void file_filepro(t_file1 **file, t_all1 **all, int i, int j)
{
    t_file1 *new;
    t_file1 *tmp;

    new = malloc(sizeof(t_file1));
    if (!new)
        return;
    new->file = NULL;
    new->type = 0;
    new->limiter = NULL;
    find_token(all,&new, i);
    find_file(all, &new, i, j);
    (*all)->cmd = delete_file(all, new, i);
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

void     fill_struct2(char **p, t_all1 **all)
{
    int  i;
    int  j;
    int pross;
    int size;
    char type;
    t_all1 *tmp;

    if(!p)
        return;
    size = ft_tablen(p);
    tmp = *all;
    tmp->next = NULL;
    i = 0;
    j =0;
    pross = 0;
    while (size - 1)
    {
        tmp->next = malloc(sizeof(t_all1));
        tmp = tmp->next;
        tmp->next = NULL;
        size--;
    }
    tmp = *all;
    while(p[i])
    {
        j = 0;
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
                file_filepro(&tmp->file,&tmp,j, i);
                j = 0;
            }
            else
                j++;
        }
        i++;
        tmp =tmp->next;
    }
}
