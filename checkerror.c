/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkerror.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallaoui <mallaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 23:12:12 by aerraoui          #+#    #+#             */
/*   Updated: 2023/03/11 18:31:48 by mallaoui         ###   ########.fr       */
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
            return(0); 
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
    return(i);
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
   return (1);
}
