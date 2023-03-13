/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallaoui <mallaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 15:42:25 by mallaoui          #+#    #+#             */
/*   Updated: 2023/03/10 15:06:51 by mallaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*read_line(char *prompt)
{
	char	*line;

	line = NULL;
	write(1, prompt, ft_strlen(prompt));
	line = get_next_line(0);
	if (line == NULL)
		return (NULL);
	return (line);
}

void    ft_check_heredoc(t_all1 *all)
{
    t_all1 *tmp;

    while (tmp)
    {
        while (file){
            if (file->type == 2)
                open_here_doc();
            file = file->next;
        }
        tmp = tmp->next;
    }
}

void    ft_check_heredoc(t_all1 **all)
{
    t_all1 *tmp;

    tmp = *all;
    while (tmp)
    {
        while (file){
            if (file->type == 2)
                open_here_doc();
            file = file->next;
        }
        tmp = tmp->next;
    }
}