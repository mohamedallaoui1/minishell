/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerraoui <aerraoui <marvin@42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 12:41:23 by mallaoui          #+#    #+#             */
/*   Updated: 2023/03/03 17:58:32 by aerraoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// t_file  *fill_file(t_file **inf, char *p, int A, int    i)
// {
//     t_file *new;
//     t_file *tmp;

//     new = malloc(sizeof(t_file));
//     if (!new)
//         return (NULL);
//     new->file = p;
//     new->append = A;
//     if (i == 0)
//         new->type = ft_strdup("infile");
//     else if (i == 1)
//         new->type = ft_strdup("outfile");
//     else if (i == 2)
//         new->type = ft_strdup("limiter");
//     new->next = NULL;
//     if (!*inf)
//         *inf = new;
//     else
//     {
//         tmp = *inf;
//         while (tmp->next)
//             tmp = tmp->next;
//         tmp->next = new;
//     }
//     return (*inf);
// }

// // t_file    *fill_file(t_file **inf, char *p, int A)
// // {
// //     t_file *new;
// //     t_file *tmp;

// //     new = malloc(sizeof(t_file));
// //     new->file = p;
// //     new->A = A;
// //     new->next = NULL;
// //     if (!*inf)
// //         *inf = new;
// //     else
// //     {
// //         tmp = *inf;
// //         while (tmp->next)
// //             tmp = tmp->next;
// //         tmp->next = new;
// //     }
// //     return (*inf);
// // }

// void    print_infile(t_file *inf)
// {
//      if (inf->file == NULL)
//          return ;
//     while (inf)
//     {
//         printf(" {file==> %s Type==> %s Append --> %d}    || ",inf->file, inf->type, inf->append);
//         inf = inf->next;
//     }
//     printf("\n");
// }

// void    fill_cmds(char *p, t_all *all)
// {
//     char **tmp;
//     int i;
//     int k;
//     int j;

//     i = 0;
//     k = 0;
//     j = 0;
//     all->file = NULL;
//     tmp = ft_split(p, ' ');
//     all->proccess = p;
//     all->cmd = tmp[0];
//     while (tmp[i])
//     {
//         if (tmp[i][0] == '-')
//             all->cmd = ft_strjoin(tmp[0], tmp[i]);
//         else if (tmp[i][0] == '<')
//         {
//             if (tmp[i][1] == '<')
//             {
//                 i++;
//                 all->A = 0;
//                 fill_file(&all->file, tmp[i], all->A, 2);
//             }
//             else
//             {
//                 i++;
//                 all->A = 0;
//                 fill_file(&all->file, tmp[i], all->A, 0);
//             }
//         }
//         else if (tmp[i][0] == '>')
//         {
//             if (tmp[i][1] == '>')
//                 all->A = 1;
//             else
//                 all->A = 0;
//             i++;
//             fill_file(&all->file, tmp[i], all->A, 1);
//         }
//         i++;
//     }
//     printf("===================\n");
//     printf("proccess--> %s\n",all->proccess);
//     printf("cmd--> %s\n",all->cmd);
//     if (all->file)
//         print_infile(all->file);
//     printf("===================\n");
// }

// int     ft_tablen(char **p)
// {
//     int i;

//     i = 0;
//     while (p[i])
//         i++;
//     return (i);
// }

// void    fill_struct(char **p, t_all   *all)
// {
//     int i;
//     int size;
//     t_all *tmp;

//     i = 0;
//     if (!*p)
//         return ;
//     tmp = all;
//     size = ft_tablen(p);
//     while (size)
//     {
//         tmp->next = malloc(sizeof(t_all));
//         tmp = tmp->next;
//         tmp->next = NULL;
//         //initialize(tmp);
//         size--;
//     }
//     while (p[i] && all)
//     {
//         fill_cmds(p[i], all);
//         all = all->next;
//         i++;
//     }
// }

void    fill_env(t_list **env)
{
    int i;

    i = 0;
    *env = NULL;
    while (environ && environ[i])
        ft_lstadd_back(env, ft_lstnew(environ[i++]));
}
