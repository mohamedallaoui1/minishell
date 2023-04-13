/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallaoui <mallaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 09:17:31 by mallaoui          #+#    #+#             */
/*   Updated: 2023/04/13 09:52:10 by mallaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_content(t_list *env, char *p)
{
	t_list	*tmp1;
	int		i;
	char	*check;
	char	*p1;

	i = 0;
	tmp1 = env;
	check = ft_join(p, "=");
	while (tmp1)
	{
		if (ft_strncmp(tmp1->content, check, ft_strlen(check)) == 0)
		{
			free(check);
			while (((char *)tmp1->content)[i] != '=')
				i++;
			p1 = ft_strdup(tmp1->content + i + 1);
			return (p1);
		}
		tmp1 = tmp1->next;
	}
	free(check);
	return (NULL);
}

void	mini_expand(char **p, char **new, t_list *env, t_expnd *vars)
{
	char	*s;
	char	*check;

	s = NULL;
	check = NULL;
	if ((*p)[vars->i] == '$')
	{
		if (mini_ex_part1(p, new, &vars))
			;
		else if (mini_ex_part2(p, new, &vars, env))
			;
	}
	else
		(*new)[(vars)->j++] = (*p)[(vars)->i++];
}

void	part2_child_hhhh(char **p, char **new, t_expnd **vars)
{
	if ((*p)[(*vars)->i] == '$' && (*p)[(*vars)->i + 1] == '\"')
	{
		while ((*p)[(*vars)->i] && (*p)[(*vars)->i] != '\"')
			(*new)[(*vars)->j++] = (*p)[(*vars)->i++];
		(*new)[(*vars)->j++] = (*p)[(*vars)->i++];
	}
	else
			(*new)[(*vars)->j++] = (*p)[(*vars)->i++];
}

int	mini_ex_part2(char **p, char **new, t_expnd **vars, t_list *env)
{
	int		l;
	char	*s;
	char	*check;

	check = NULL;
	s = NULL;
	l = 0;
	if (ft_isalnum((*p)[(*vars)->i + 1]))
	{
		l = 1;
		(*vars)->i++;
		s = ft_strdupx(ft_firstword(&(*p)[(*vars)->i]));
		check = get_content(env, s);
		if (check)
			fill_content(&(*new), check, &(*vars)->j);
		(*vars)->i += ft_strlen(s);
		(free(check), free(s));
	}
	else
		part2_child_hhhh(p, new, vars);
	return (l);
}

int	mini_ex_part1(char **p, char **new, t_expnd **vars)
{
	char	*tmp;
	int		k;
	int		l;

	tmp = NULL;
	k = 0;
	l = 0;
	if ((*p)[(*vars)->i + 1] == '$')
	{
		l = 1;
		(*vars)->i++;
		(*new)[(*vars)->j++] = '$';
	}
	else if ((*p)[(*vars)->i + 1] == '?')
	{
		l = 1;
		(*vars)->i += 2;
		tmp = ft_itoa((long)glob.exit_status);
		while (tmp[k])
			(*new)[(*vars)->j++] = tmp[k++];
		free(tmp);
	}
	return (l);
}
