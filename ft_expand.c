/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallaoui <mallaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 19:18:17 by aerraoui          #+#    #+#             */
/*   Updated: 2023/04/12 00:34:55 by mallaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

char	*get_content(t_list *env, char *p)
{
	char	*tmp;
	t_list	*tmp1;
	int		i;
	char	*check;
	char *p1;
	

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

char	*ft_strdupX(char *s1)
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

void	norm_count_total_1(char *p, int	*i, int	*cont_size, t_list *env)
{
	char	*s;
	char	*content;
	char	*tmp;

	if (p[(*i)] == '$')
	{
		if (p[(*i) + 1] == '$')
		{
			(*cont_size)++;
			(*i)++;
		}
		else if (p[(*i) + 1] == '?')
		{
			tmp = ft_itoa((long)glob.exit_status);
			(*cont_size) += ft_strlen(tmp);
			(*i) += 2;
			free(tmp);
		}
		else if (ft_isalnum(p[(*i) + 1]))
		{
			(*i)++;
			s = ft_strdupX(ft_firstword(&p[(*i)]));
			content = get_content(env, s);
			(*cont_size) += ft_strlen(content);
			(*i) += ft_strlen(s);
			free(s);
			free(content);
		}
		else
		{
			(*cont_size)++;
			(*i)++;
		}
	}
	else
	{
		(*cont_size)++;
		(*i)++;
	}
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
	{
		if (p[i] == '\'')
		{
			i++;
			while (p[i] && p[i] != '\'')
			{
				i++;
				cont_size++;
			}
			i++;
			cont_size += 2;
		}
		else if (p[i] == '"')
		{
			i++;
			while (p[i] && p[i] != '\"')
				norm_count_total_1(p, &i, &cont_size, env);
			i++;
			cont_size += 2;
		}
		else
			norm_count_total_1(p, &i, &cont_size, env);
	}
	return (cont_size);
}

void	fill_content(char **new, char *cont, int *i)
{
	int	j;

	j = 0;
	if (cont)
	{
		while (cont[j])
			(*new)[(*i)++] = cont[j++];
	}
}

void	mini_expand(char **p, char **new, t_list *env, t_expnd *vars)
{
	int		i;
	int		j;
	int		k;
	char	*s;
	char	*tmp;
	char	*check;

	i = vars->i;
	j = vars->j;
	s = NULL;
	check = NULL;
	tmp = NULL;
	if ((*p)[i] == '$')
	{
		if ((*p)[i + 1] == '$')
		{
			i++;
			(*new)[j++] = '$';
		}
		else if ((*p)[i + 1] == '?')
		{
			i += 2;
			k = 0;
			tmp = ft_itoa((long)glob.exit_status);
			while (tmp[k])
				(*new)[j++] = tmp[k++];
			free(tmp);
		}
		if (ft_isalnum((*p)[i + 1]))
		{
			i++;
			s = ft_strdupX(ft_firstword(&(*p)[i]));
			check = get_content(env, s);
			if (check)
				fill_content(&(*new), check, &j);
			i += ft_strlen(s);
			free(check);
			free(s);
		}
		else
		{
			if ((*p)[i] == '$' && (*p)[i + 1] == '\"')
			{
				while ((*p)[i] && (*p)[i] != '\"')
					(*new)[j++] = (*p)[i++];
				(*new)[j++] = (*p)[i++];
			}
			else
				(*new)[j++] = (*p)[i++];
		}
	}
	else
		(*new)[j++] = (*p)[i++];
	vars->i = i;
	vars->j = j;
}

char	*expand(t_list *env, char *p)
{
	t_expnd	vars;

	vars.size = count_total(env, p);
	vars.i = 0;
	vars.j = 0;
	vars.new = NULL;
	vars.new = calloc (vars.size + 1, 1);
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
