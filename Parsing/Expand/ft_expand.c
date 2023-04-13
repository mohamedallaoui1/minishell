/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallaoui <mallaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 19:18:17 by aerraoui          #+#    #+#             */
/*   Updated: 2023/04/13 17:11:00 by mallaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_strdupx(char *s1)
{
	int		i;
	char	*s;

	i = 0;
	s = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!s)
		return (NULL);
	while (s1[i])
	{
		s[i] = s1[i];
		i++;
	}
	s[i] = '\0';
	free(s1);
	return (s);
}

int	count_total(t_list *env, char *p)
{
	int		i;
	int		j;
	int		cont_size;

	i = 0;
	j = 0;
	cont_size = 0;
	while (p[i])
		count_total_while(p, &i, &cont_size, env);
	return (cont_size);
}

void	the_while_statement(t_list *env, char *p, t_expnd	vars)
{
	while (p[vars.i])
	{
		if (p[vars.i] == '\'')
		{
			vars.new[vars.j++] = p[vars.i++];
			while (p[vars.i] && p[vars.i] != '\'')
				vars.new[vars.j++] = p[vars.i++];
			vars.new[vars.j++] = p[vars.i++];
		}
		else if (p[vars.i] == '\"')
		{
			vars.new[vars.j++] = p[vars.i++];
			while (p[vars.i] && p[vars.i] != '\"')
				mini_expand(&p, &vars.new, env, &vars);
			vars.new[vars.j++] = p[vars.i++];
			vars.new[vars.j] = '\0';
		}
		else
			mini_expand(&p, &vars.new, env, &vars);
	}
	vars.new[vars.j] = '\0';
}

char	*expand(t_list *env, char *p)
{
	t_expnd	vars;

	vars.size = count_total(env, p);
	vars.i = 0;
	vars.j = 0;
	vars.new = NULL;
	vars.new = calloc (vars.size + 1, 1);
	the_while_statement(env, p, vars);
	free(p);
	return (vars.new);
}

void	expandfile(t_list *env, t_file1 *file)
{
	if (file != NULL)
	{
		while (file->next)
		{
			if (file->type == HER)
				file = file->next;
			else
			{
				file->file = expand(env, file->file);
				file = file->next;
			}
		}
	}
}
