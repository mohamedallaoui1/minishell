#include "minishell.h"

void    skip_spaces(char *p, int *i)
{
    while (p[*i] && p[*i] == ' ')
        (*i)++;
}