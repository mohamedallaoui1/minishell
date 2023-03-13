/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallaoui <mallaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 00:49:53 by aerraoui          #+#    #+#             */
/*   Updated: 2023/03/11 18:32:32 by mallaoui         ###   ########.fr       */
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

void initialize(t_all *all)
{
    all->cmd = NULL;
    all->A = 0;
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
      if (inf->file == NULL)
          return ;
     while (inf)
     {
         printf(" {file==> %s Type==> %d Append --> %d}    || ",inf->file, inf->type, inf->append);
         inf = inf->next;
     }
     printf("\n");
 }
int main()
{
    char **p;
    int i;
    char *buffer;
    t_list  *env;
    t_all1 *all;
    t_file1 *file;

    env = NULL;
    all = NULL;
    all = malloc(sizeof(t_all1));
    if(!all)
        return (1);
    file = malloc(sizeof(t_file1));
    if(!file)
        return (2);
    // initialize(all);

    fill_env(&env);
    while(1)
    {
            i =0;
            buffer = readline("\e[1;31mminishell> \e[0;m");
            add_history(buffer);
            buffer = fix_buffer(buffer);
            buffer = expand(env, buffer);
            printf("buffer = %s\n",buffer);
            if(ft_eroro(buffer))
            {
                p = ft_split(buffer,'|');
                fill_struct2(p, &all);
            }
            else
                free(buffer);
            // printf("the cmd is : %s\n", all->cmd);
            // printf("the problem is : %s", all->cmd);
            while(all->next)
            {
                printf("all->cmd---> %s\n",all->cmd);
                if (all->file)
                    print_infile(all->file);
                all =all->next;
            }
    }
}