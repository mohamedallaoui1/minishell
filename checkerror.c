/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkerror.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallaoui <mallaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 23:12:12 by aerraoui          #+#    #+#             */
/*   Updated: 2023/03/25 17:26:29 by mallaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include"minishell.h"

int ft_erorr(char *buff,char bu,int i)
{
    if(bu == '|')
    {
        i++;
       while (buff[i] && buff[i] == ' ')
            i++;
            
       if(buff[i]  == '|')
       {
            return(-1);
       }
        return(i);
    }
    else
    {
        i++;
        while(buff[i] && buff[i] != bu)
            i++;
            return(i);
    }
}

int ft_check_erorr(char *buff)
{
    char *s;
    int i;

    i =0;
    s =ft_firstword(buff);
    if( s && s[0] =='|')
    {
        printf("bash: syntax error near unexpected token `|'\n");
            return(free(s),0); 
    }
    while(buff[i])
    {
        if(buff[i] =='|' || buff[i] == '"' || buff[i] == '\'')
        {
             i =ft_erorr(buff,buff[i],i);
            if(i == -1)
            {
                printf("bash: syntax error near unexpected token `|'\n");
                return(0);
            }
        }
        else
            i++;
    }
    i= 0;
    while(buff[i])
        i++;
    i--;
    while(buff[i] == ' ')
        i--;
    if(buff[i] == '|')
    {
       printf("bash: syntax error near unexpected token `|'\n");
        return(0);
    }
    return(free(s),1);
}

int number_que(char *buff)
{
    int i;
    int countdouble = 1;
    int countsingla = 1;
    i = 0;
    char c;
    while(buff[i])
    {
        if(buff[i] == '\'')
        {
            i++;
            countsingla++;
            while(buff[i] && buff[i] != '\'')
                i++;
            if(buff[i++] == '\'' )
                countsingla++; 

        }
        else if(buff[i] == '"')
        {
            i++;
            countdouble++;
            while(buff[i] && buff[i] != '\"')
                i++;
            if(buff[i++] == '"' )
                countdouble++;
        }
        i++;
    }
    printf("couns --> %d -- counnd -->%d\n",countdouble,countsingla);
    if(countsingla %2 == 0 && countdouble % 2== 0 )
       return(1);
    else
        return(0);
}

int check_token1(char *buff)
{
    int i ;
    char type;

    i =0;
    while(buff[i])
    {
        if(buff[i] == '\'' || buff[i] == '"')
        {
            type = buff[i++];
            while (buff[i] && buff[i] != type)
            i++; 
        }
        if(buff[i] == '<' )
        {
           if(buff[++i] =='<')
           {
                i++;
                while(buff[i] == ' ')
                        i++;
                if(buff[i] == '<' || buff[i] == '>')
                    return (0);
           }
           else
           {
                if( buff[i] == '>')
                    return(0);
                 while(buff[i] && buff[i] == ' ')
                    i++;
                if(buff[i] == '<' || buff[i] == '>')
                    return (0);
           }
        }
            i++;
    }
    return(1);
}

int check_token2(char *buff)
{
    int i ;
    char type;

    i =0;
    while(buff[i])
    {
        if(buff[i] == '\'' || buff[i] == '"')
        {
            type = buff[i++];
            while (buff[i] && buff[i] != type)
            i++; 
        }
        if(buff[i] == '>' )
        {
           if(buff[++i] =='>')
           {
                i++;
                while(buff[i] == ' ')
                        i++;
                if(buff[i] == '<' || buff[i] == '>')
                    return (0);
           }
           else
           {
                if( buff[i] == '<')
                    return(0);
                 while(buff[i] && buff[i] == ' ')
                    i++;
                if(buff[i] == '<' || buff[i] == '>')
                    return (0);
           }
        }
            i++;
    }
    return(1);
}

int check_token0(char *buff)
{
    int i;
    int j;
    char **p;
    char type;
    
    i = 0;
    p = ft_split(buff,'|');
    while(p && p[i])
    {
        j = 0;
        while(p[i][j] )
        {
            if(p[i][j] == '<' || p[i][j] == '>')
            {
                if(!p[i][j+1])
                    return(ft_free(p),0);
                type = p[i][j] ;
                j++;
                if(p[i][j] == type)
                    j++;
                while(p[i][j] == ' ')
                    j++;
                if(!p[i][j])
                    return(ft_free(p),0);
            }
                j++;
        }
        i++;
    }
    return(ft_free(p),1);
}

int number_here(char *buff)
{
    int i;
    int count ;

    count = 0;
    i = 0;
    while(buff[i])
    {
        if(buff[i] == '<' && buff[i+1] == '<')
        {
            count++;
            i +=2;
        }
        else
            i++;
    }
    if(count > 15)
    {
        printf("minishell: maximum here-document count exceeded\n");
        exit(2);
    }
    else
        return (1);
}
int ft_eroro(char *buff)
{
    int i;
    int c;
    c = ft_check_erorr(buff);
     if(c == 0)
         return(0); 
   i = check_quotes(buff);
   if(!i)
   {
        printf("error in number of \" or '\n"); 
        return(0);
   }
   if(!check_token1(buff) || !check_token2(buff))
   {
    printf("syntax error near unexpected token `>' or `<'\n");
    return(0);
   }
   if(!check_token0(buff))
   {
        printf("syntax error near unexpected token `newline\n");
        return(0);
   }
   if(!number_here(buff))
        return(0);
   return (1);
}
