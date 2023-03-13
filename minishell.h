/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallaoui <mallaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 16:53:15 by aerraoui          #+#    #+#             */
/*   Updated: 2023/03/11 18:15:59 by mallaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H 



extern char **environ;

#define HER 2
#define OUT 0
#define INF 1

typedef struct s_file
{
    char *file; 
    char *type;
    int  append;
    struct s_file *next;
}           t_file;

typedef struct s_all
{
    char *cmd;
    t_file *file;
    int    A;
    char *proccess;
    int     fd_here_doc;
    struct s_all *next;
}           t_all;

typedef struct s_fila
{
    char *file; 
    int type ;
    int  append;
    struct s_fila *next;
}           t_file1;

typedef struct s_all1
{
    char *cmd;
    t_file1 *file;
    int    A;
    struct s_all1 *next;
}       t_all1;

# include "readline/readline.h"
# include <stdlib.h>
# include "libft/libft.h"
# include <readline/history.h>

char    **split_pipe(char *buff);
void    skip_spaces(char *p, int *i);
void    fill_struct(char **p, t_all *all);
void    fill_struct2(char **p, t_all1   **all);
int    check_quotes(char *p);
void initialize(t_all *all);
int ft_eroro(char *buff);
char *ft_firstword(char *p);
void    fill_env(t_list **env);
void	ft_free(char **p);
char *expand(t_list *env, char *p);


#endif