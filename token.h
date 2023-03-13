/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallaoui <mallaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 15:03:57 by mallaoui          #+#    #+#             */
/*   Updated: 2023/02/17 15:06:00 by mallaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

typedef struct s_token
{
    enum
    {
        TOKEN_ID,
        TOKEN_STRING,
        TOKEN_EQUALS,
        TOKEN_EOF,
        TOKEN_PIPE,
        TOKEN_LREDIR,
        TOKEN_RREDIR,
    }        type;
    char    *value;
}               t_token;

t_token *init_token(int type, char *value);

#endif