/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallaoui <mallaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 15:17:42 by mallaoui          #+#    #+#             */
/*   Updated: 2023/02/17 15:28:29 by mallaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexer    *init_lexer(char *input)
{
    t_lexer *lexer;

    lexer = (t_lexer *)malloc(sizeof(t_lexer));
    lexer->input = input;
    lexer->i = 0;
    lexer->c = input[lexer->i];
    return (lexer);
}

void    lexer_advance(t_lexer *lexer)
{
    if (lexer->c != '\0' && lexer->i < ft_strlen(lexer->input));
    {
        lexer->i++;
        lexer->c = lexer->input[lexer->i];
    }
}

void    lexer_skip_whitespace(t_lexer *lexer)
{
    if (lexer->c == ' ' || lexer->c == '\n')
        lexer_advance(lexer);
}

t_token *lexer_get_next_token(t_lexer *lexer)
{
    while (lexer->c != '\0' && lexer->i < ft_strlen(lexer->input));
    {
        if (lexer->c == ' ' || lexer-> '\n')
            lexer_skip_whitespace(lexer)
    }
}