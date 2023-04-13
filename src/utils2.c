/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallaoui <mallaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 22:06:09 by mallaoui          #+#    #+#             */
/*   Updated: 2023/04/13 22:08:44 by mallaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*delet_speace(char *p)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	new = ft_calloc(ft_strlen(p) + 1, 1);
	while (p[i])
	{
		if (p[i] >= 8 && p[i] < 32)
		{
			new[j++] = 32;
			i++;
		}
		else
			new[j++] = p[i++];
	}
	new[j] = '\0';
	free(p);
	return (new);
}

void	reinitialize(t_everything **shell)
{
	(*shell)->all = NULL;
	(*shell)->file = NULL;
	(*shell)->vars = NULL;
	(*shell)->all = malloc(sizeof(t_all1));
	(*shell)->file = malloc(sizeof(t_file1));
	(*shell)->vars = malloc(sizeof(t_exec));
	initialize(&(*shell)->all);
}

void	free_everything_shell(t_everything **shell)
{
	free((*shell)->buffer);
	free((*shell)->vars);
	free((*shell)->all);
	free((*shell)->file);
}

void	get_attr(void)
{
	tcgetattr(STDIN_FILENO, &glob.old_attr);
	tcgetattr(STDIN_FILENO, &glob.new_attr);
	tcgetattr(STDIN_FILENO, &glob.reset_attr);
	glob.old_attr.c_lflag &= ~(ECHOCTL);
}
