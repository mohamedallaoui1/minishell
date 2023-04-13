/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallaoui <mallaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 14:23:20 by mallaoui          #+#    #+#             */
/*   Updated: 2023/04/13 07:04:29 by mallaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_struct(t_exec **vars, t_list *env)
{
	int	i;

	i = 0;
	(*vars)->i = 0;
	(*vars)->path = NULL;
	(*vars)->splited = NULL;
	(*vars)->double_env = NULL;
	(*vars)->env = env;
	(*vars)->duppin = malloc(sizeof(t_dup));
	(*vars)->duppin->infile = 0;
	(*vars)->duppin->outfile = 1;
}


int    open_files(t_exec **vars, t_file1 *file, int check)
{
    t_file1 *tmp;
    char *gg;
    char **cc;

    tmp = file;
    while(tmp)
    {
        gg = ft_strdup1(tmp->file);
        tmp->file = ft_wildcard(tmp->file);
        cc = ft_split(tmp->file, ' ');
        if ((ft_strchr_normal(gg, '*') && ft_tablen(cc) > 1)|| !check_ambiguous(&tmp,(*vars)->env ))
            (ft_printf(2, "bash: %s: ambiguous redirect\n", gg), glob.exit_status = 1, ft_free(cc),exit(glob.exit_status));
        else if (tmp->type == INF)
        {  
            (*vars)->duppin->infile = open(tmp->file, O_RDONLY);
            if ((*vars)->duppin->infile < 0)
            {
                perror("Error");
                if (check)
                    glob.exit_status = 1, exit(glob.exit_status);
                else
                    return (1);
            }
        }
        else if (tmp->type == HER)
        {
            (*vars)->duppin->infile = open(tmp->file, O_RDONLY);
            if ((*vars)->duppin->infile < 0)
            {
                perror("Error");
                if (check)
                    glob.exit_status = 1, exit(glob.exit_status);
                else
                    return (1);
            }
        }
        else if (tmp->type == OUT || tmp->type == APP)
        {
            
            if (tmp->type == APP)
                (*vars)->duppin->outfile = open(tmp->file, O_RDWR | O_CREAT | O_APPEND, 0644);
            else
                (*vars)->duppin->outfile = open(tmp->file, O_RDWR | O_CREAT | O_TRUNC, 0644);
            if ((*vars)->duppin->outfile < 0)
            {
                perror("Error");
                if (check)
                    glob.exit_status = 1, exit(glob.exit_status);
                else
                    return (1);
            }
        }
        tmp = tmp->next;
    }
    return (0);
}

void    indexing(t_all1 **all)
{
    t_all1  *temp;
    int i;

    temp = *all;
    i = 0;
    while(temp)
    {
        temp->index = i;
        i++;
        temp = temp->next;
    }
}

void    check_built_ins(int fd, int check, char **p, t_exec *vars)
{
    if (!ft_cmp(p[0], "unset"))
        ft_unset(fd, check, p, vars->env);
    else if (!ft_cmp(p[0], "cd"))
        ft_cd(fd, check, p, vars->env);
    else if (!ft_cmp(p[0], "env"))
        ft_env(fd, check, p, vars->env);
    else if (!ft_cmp(p[0], "export"))
        ft_export(fd, check, p, vars->env);
    else if (!ft_cmp(p[0], "exit"))
        ft_exit(fd, check, p, vars->env);
    else if (!ft_cmp(p[0], "pwd"))
        ft_pwd(fd, check, p, vars->env);
    else if (!ft_cmp(p[0], "echo"))
        ft_echo(fd, check, p, vars->env);
}

int is_built_in(char *p)
{
    if (!ft_cmp(p, "unset"))
        return (1);
    else if (!ft_cmp(p, "cd"))
        return (1);
    else if (!ft_cmp(p, "env"))
        return (1);
    else if (!ft_cmp(p, "export"))
        return(1);
    else if (!ft_cmp(p, "exit"))
        return (1);
    else if (!ft_cmp(p, "pwd"))
        return (1);
    else if (!ft_cmp(p, "echo"))
        return (1);
    return (0);
}

void    first(t_exec **vars, t_all1 *all)
{
    t_exec *tmp;

    tmp = *vars;
    close(tmp->fd[0]);
    if (tmp->duppin->infile != 0)
        dup2(tmp->duppin->infile, 0);
    else
        dup2(tmp->in, 0);
    if (tmp->duppin->outfile != 1)
        dup2(tmp->duppin->outfile, 1);
    else if (all->next != NULL)
        dup2(tmp->fd[1], 1);
    else
    {
        dup2(tmp->out, 1);
        close(tmp->fd[1]);
    }
    join_and_check_if_excutable(tmp, all);
}

void    last(t_exec **vars, t_all1 *all)
{
    t_exec *tmp;

    tmp = *vars;
    close(tmp->fd[1]);
    close(tmp->in);
    if (tmp->duppin->infile != 0)
        dup2(tmp->duppin->infile, 0);
    if (tmp->duppin->outfile != 1)
        dup2(tmp->duppin->outfile, 1);
    join_and_check_if_excutable(tmp, all);
}

void    middle(t_exec **vars, t_all1 *all)
{
    t_exec *tmp;

    tmp = *vars;
    close(tmp->in);
    close(tmp->out);
    close(tmp->fd[0]);
    if (tmp->duppin->infile != 0)
        dup2(tmp->duppin->infile, 0);
    if (tmp->duppin->outfile != 1)
        dup2(tmp->duppin->outfile, 1);
    else
        dup2(tmp->fd[1], 1);
    join_and_check_if_excutable(tmp, all);
}

int     only_white_spaces(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] != ' ' && str[i] != '\t')
            return (0);
        i++;
    }
    return (1);
}

void    execute(t_exec **vars, t_all1 *all)
{
    tcsetattr(STDIN_FILENO, TCSANOW, &glob.new_attr);
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
    open_files(vars, all->file, 1);
    if (all->cmd[0] == 0 || only_white_spaces(all->cmd))
        exit(glob.exit_status);
    if (all->index == 0)
        first(vars, all);
    else if (all->next == NULL && all->index != 0)
        last(vars, all);
    else
        middle(vars, all);
}

void    free_everything(t_exec *vars)
{
    if (vars->path)
        free(vars->path);
    if (vars->double_env)
        ft_free(vars->double_env);
    if (vars->duppin)
        free(vars->duppin);
    if (vars->splited)
        ft_free(vars->splited);
}



void    execution(t_all1 *all, t_exec **vars, t_list *env)
{
    t_exec  *tmp;
    t_all1  *temp;
    char    *fix;
    char **p;
    int save;

    tmp = *vars;
    temp = all;

    init_struct(&tmp, env);
    indexing(&all);
    tmp->in = dup(0);
    tmp->out = dup(1);
    p = NULL;
    p = ft_split(all->cmd, ' ');
    destroy_qoute(p);
    if (is_built_in(p[0]) && all->next == NULL)
    {
        open_files(vars, all->file, 0);
        check_built_ins(tmp->duppin->outfile, 0, p, (*vars));
        free_everything(tmp); 
        return ;
    }
    else
        ft_free(p);
    while(temp)
    {
        pipe(tmp->fd);
        tmp->duppin->infile = 0;
        tmp->duppin->outfile = 1;
        tmp->id = fork();
        if ((*vars)->id == 0)
            execute(vars, temp);
        else
        {
            signal(SIGINT, handle_1);
            signal(SIGQUIT, handle_2);
            save = tmp->fd[0];
            dup2(save, 0);
            if (tmp->duppin->infile != 0)
                close(tmp->duppin->infile);
            if (tmp->duppin->outfile != 1)
                close(tmp->duppin->outfile);
            close(tmp->fd[0]);
            close(tmp->fd[1]);
            tcsetattr(STDIN_FILENO, TCSANOW, &glob.old_attr);
        }
        temp = temp->next;
    }
    waitpid(tmp->id, &tmp->status, 0);
    if (WIFEXITED(tmp->status))
        glob.exit_status = WEXITSTATUS(tmp->status);
    if (WIFSIGNALED(tmp->status))
        glob.exit_status = WTERMSIG(tmp->status) + 128;
    while(wait(NULL) != -1);
    free_everything(tmp);
}