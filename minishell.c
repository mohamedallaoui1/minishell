/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallaoui <mallaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 00:49:53 by aerraoui          #+#    #+#             */
/*   Updated: 2023/04/12 01:29:41 by mallaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free1(char **p)
{
	int	i;

	i = 0;
	while (p[i] != 0)
	{
		free(p[i]);
		i++;
	}
	free(p);
}

void func_echo(char *str)
{

    if(!str)
        return ;
    char **p;
    char *s;
    
    p =ft_split(str,' ');
    
    if (p[0] && ft_strncmp(p[0] ,"echo",ft_strlen(p[0])) ==0)
    {
        if (p[1]&&ft_strncmp(p[1] ,"-n",2) == 0)
          {
             s =ft_strnstr(str,"-n",ft_strlen(str));
             printf("%s",s+2);
          }
          else
          {
            s=ft_strnstr(str,"echo",ft_strlen(str));
            printf("%s\n",s +4);
          }
    }
    ft_free1(p);
        
}

void func_pwd(char *str)
{
    char **p;
    char pwd[1024];
     
    p = ft_split(str,' ');
    if(p[0] && ft_strncmp(p[0],"pwd",3) == 0)
    {
        getcwd(pwd, sizeof(pwd));
        printf("%s\n", pwd);
    }
    ft_free1(p);
}

char    *fix_buffer(char *buffer)
{
    unsigned int len;
    int i;
    int j;
    char *new_string;

    len = ft_strlen(buffer);
    new_string = malloc (len * 2);
    i = 0;
    j = 0;
    while (i < len)
    {
        if (buffer[i] == '"')
        {
            new_string[j++] = buffer[i++];
            while (i < len && buffer[i] != '"')
                new_string[j++] = buffer[i++];
            new_string[j++] = buffer[i++];
        }
        else if (buffer[i] == '<' || buffer[i] == '>')
        {
            if (buffer[i] == '>' && buffer[i + 1] == '>' && buffer[i - 1] == ' ')
                new_string[j++] = buffer[i++];
            if (buffer[i] == '<' && buffer[i + 1] == '<' && buffer[i - 1] == ' ')
                new_string[j++] = buffer[i++];
            if (i > 0 && buffer[i - 1] != ' ' && buffer[i - 1] != '<' && buffer[i - 1] != '>')
                new_string[j++] = ' ';
            new_string[j++] = buffer[i++];
            if (i < len && buffer[i] != ' ' && buffer[i] != '<' && buffer[i] != '>')
                new_string[j++] = ' ';
        }
        else
            new_string[j++] = buffer[i++];
    }
    new_string[j] = '\0';
    free(buffer);
    return (new_string);
}

 void    print_infile(t_file1 *inf)
 {
    printf("====================================================\n");
    while (inf)
    {
        printf("{file==> %s | Type==> %d | limiter===> %s } \n",inf->file, inf->type, inf->limiter);
        inf = inf->next;
    }
    printf("\n");
    printf("====================================================\n");
 }

void initialize(t_all1 **all)
{
    (*all)->cmd = NULL;
    (*all)->file = NULL;
    (*all)->next = NULL;
}

void free_all(t_all1 **all)
{
    t_all1 *tmp;
    t_file1 *tmpfile;
    
    tmp = (*all);
    
    while(tmp)
    {
        free(tmp->cmd);
        while(tmp->file)
        {
            tmpfile = tmp->file;
            if(tmpfile->type == HER)
                free(tmpfile->limiter);
            if(tmpfile->file)
                free(tmpfile->file);
            tmp->file =tmp->file->next;
            free(tmpfile);
            tmpfile = tmp->file;
        }
        free(tmp->file);
        (*all)=(*all)->next;
        free(tmp);
        tmp = (*all);
    }
}

void    handle(int signum)
{
    glob.exit_status = 1;
    write(1, "\n", 1);
    rl_replace_line("", 0);
    rl_on_new_line();
    rl_redisplay();
}

void    handle_1(int signum)
{
    write(1, "\n", 1);
    rl_replace_line("", 0);
    rl_on_new_line();
}

void    handle_2(int signum)
{
    write(1, "Quit: 3\n", 9);
    rl_replace_line("", 0);
    rl_on_new_line();
}

void    free_struct(t_all1 **all)
{
    printf("the cmd is %p\n",(*all)->cmd);
    exit(0);
    if ((*all)->cmd)
        free((*all)->cmd);
    if ((*all)->file)
    {
        if ((*all)->file->file)
            free((*all)->file->file);
        if ((*all)->file->limiter)
            free((*all)->file->limiter);
        free((*all)->file);
    }
    free((*all));
}
int main()
{
    char **p;
    int i;
    char *buffer;
    t_list  *env;
    t_all1 *all;
    t_all1 *tmp;
    t_file1 *file;
    t_exec  *vars;
    char *buff;

    env = NULL;   
    fill_env(&env);
    tcgetattr(STDIN_FILENO, &glob.old_attr);
    tcgetattr(STDIN_FILENO, &glob.new_attr);
    glob.old_attr.c_lflag &= ~(ECHOCTL);
    while(1)
    {
        signal(SIGQUIT, SIG_IGN);
        signal(SIGINT, handle);
        tcsetattr(STDIN_FILENO, TCSANOW, &glob.old_attr);
        all = NULL;
        file = NULL;
       vars = NULL;
        all = malloc(sizeof(t_all1));
        file = malloc(sizeof(t_file1));
       vars = malloc(sizeof(t_exec));
        initialize(&all);
        i = 0;
        buff = readline("minishell> ");
        if (!buff)
            ft_printf(2, "exit\n"), exit(0);
        add_history(buff);
        buffer = ft_strdup(buff);
        free(buff);
         buffer = fix_buffer(buffer);
        if (buffer && ft_cmp(buffer,"\0") != 0)
        {
            if(ft_eroro(buffer))
            {
                p = ft_split(buffer,'|');
                fill_struct2(p, &all);
                tmp = all;
                ft_free(p); 
                while(all)
                {
                    all->cmd = expand(env,all->cmd);
                    all->cmd = ft_wildcard(all->cmd);
                    if (all->file)
                    {
                        expandfile(env,all->file);
                        open_here_doc(&all->file,env);
                        //  print_infile(all->file);
                    }
                    all =all->next;
                 }
            all = tmp;
            execution(tmp, &vars, env);
            dup2(vars->in, 0);
            dup2(vars->out, 1);
            close(vars->in);
            close(vars->out);
            free_all(&all);
            }
        }
        free(buffer);
        free(vars);
        free(all);
        free(file);
        tcsetattr(STDIN_FILENO, TCSANOW, &glob.old_attr);
    }
}