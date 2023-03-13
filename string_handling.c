#include "minishell.h"

void    power_quotes(char *p, char c)
{
    int i = 1;

    if (p[i] == c && p[i+1] == c)
        i++;
    else
        printf("%c", p[i]);
}

int    check_quotes(char *p)
{
    int     i;
    int     j;
    int     k;

    i = 0;
    j = 0;
    k = 0;
    while (p[i])
    {
        if (p[i] == '"')
        {
            i++;
            while (p[i] && p[i] != '"')
                i++;
            j++;
        }
        else if (p[i] == '\'')
        {
            i++;
            while (p[i] && p[i] != '\'')
                i++;
            k++;
        }
        else
            i++;
    }
    if (j % 2 == 0 && k % 2 == 0)
        return (1);// closing quot exist
    else
        return (0);// no closing quot > error
}