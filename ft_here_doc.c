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

void    ft_here_doc(t_all *all, )
{
    int id;
    char    *line;

    id = fork()
    if (id == 0)
    {
        all->ft_here_doc = open ("/tmp/here_doc", O_RDWR | O_CREATE | O_APPEND, 0644);
        if (all->ft_here_doc < 0)
            perror("Error");
	    while (1)
	    {
	    	line = read_line("heredoc> ");
	    	write(vars->fd_here_doc, line, ft_strlen(line));
	    }
    }
}