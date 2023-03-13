/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerraoui <aerraoui <marvin@42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 19:18:17 by aerraoui          #+#    #+#             */
/*   Updated: 2023/02/28 19:53:06 by aerraoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

char *get_content(t_list *env, char *p)
{
    char *tmp;
    t_list *tmp1;
    int i;
    char *check;

    i = 0;
    tmp1 = env;
    check = ft_strjoin(p, "=");
    while (tmp1)
    {
        if (ft_strncmp(tmp1->content, check, ft_strlen(check)) == 0)
        {
            free(check);
            while (((char *)tmp1->content)[i] != '=')
                i++;
            return (tmp1->content + i + 1);
        }
        tmp1 = tmp1->next;
    }

    return (NULL);
}

int count_total(t_list *env, char *p)
{
    int i;
    int j;
    int cont_size;
    char *s;
    char *content;

    i = 0;
    j = 0;
    cont_size = 0;
    if (p[i] == '\'')
    {
        i++;
        cont_size++;
        while (p[i] && p[i] != '\'')
        {
            i++;
            cont_size++;
        }
    }
    while (p[i])
    {
        if (p[i] == '$')
        {
            if (p[i + 1] == '$')
            {
                cont_size++;
                i++;
            }
            else if (ft_isalnum(p[i + 1]))
            {
                i++;
                s = ft_firstword(&p[i]);
                content = get_content(env, s);
                cont_size += ft_strlen(content);
                i += ft_strlen(s);
            }
            else
            {
                cont_size++;
                i++;
            }
        }
        else
        {
            cont_size++;
            i++;
        }
    }
    return (cont_size);
}

void    fill_content(char **new, char *cont, int *i)
{
    int j;

    j = 0;
    if (cont)
    {
        while (cont[j])
            (*new)[(*i)++] = cont[j++];
    }
}

char *expand(t_list *env, char *p)
{
    int i;
    int j;
    char *new;
    char *s;
    int size;

    size = count_total(env, p);
    i = 0;
    j = 0;
    new = malloc (size + 1);
    if (p[i] == '\'')
    {
            new[j++] = p[i++];
        while (p[i] && p[i] != '\'')
            new[j++] = p[i++];
    }
    while (p[i])
    {
        if (p[i] == '$')
        {
            if (p[i + 1] == '$')
            {
                i++;
                new[j++] = '$';
            }
            else if (ft_isalnum(p[i + 1]))
            {
                i++;
                s = ft_firstword(&p[i]);
                if (get_content(env, s))
                    fill_content(&new, get_content(env, s), &j);
                i += ft_strlen(s);
                free(s);
            }
            else
                new[j++] = p[i++];
        }
        else
            new[j++] = p[i++];
    }
    new[j] = '\0';
    return (new);
}