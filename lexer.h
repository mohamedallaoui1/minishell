/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallaoui <mallaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 14:55:13 by mallaoui          #+#    #+#             */
/*   Updated: 2023/02/17 15:25:53 by mallaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

#include "libft/libft.h"
#include "token.h"
typedef struct s_lexer
{
    char    c;
    int     i;
    char    *input;
}               t_lexer;
 
t_lexer    *init_lexer(char *input);
void    lexer_advance(t_lexer *lexer);
void    lexer_skip_whitespace(t_lexer *lexer);
void    lexer_collect_id(t_lexer *lexer);
void    lexer_advance_with_token(t_lexer *lexer, t_token *token);
void    lexer_collect_string(t_lexer *lexer);
t_token *lexer_get_next_token(t_lexer *lexer);
char    *lexer_get_current_char_as_string(t_lexer *lexer);