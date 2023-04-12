/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerraoui <aerraoui <marvin@42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 01:37:23 by aerraoui          #+#    #+#             */
/*   Updated: 2023/04/06 02:25:21 by aerraoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

void	add_export_norm(t_list **node, char *name, char *cont)
{
	if (cont)
	{
		if ((*node)->cont)
			free((*node)->cont);
		free((*node)->content);
		(*node)->content = ft_join(name, "=");
		(*node)->content = ft_strjoin((*node)->content, cont);
		(*node)->cont = ft_strdup(cont);
	}
}

void	add_export(t_list *env, char *content, char *name, char *cont)
{
	char	*a;
	char	*b;
	char	*c;
	int		size;
	t_list	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_cmp(name, tmp->name) == 0)
		{
			add_export_norm(&tmp, name, cont);
			return ;
		}
		tmp = tmp->next;
	}
	a = ft_strdup(content);
	b = ft_strdup(name);
	if (cont)
		c = ft_strdup(cont);
	else
		c = NULL;
	size = ft_lstsize(env);
	ft_lstadd_back(&env, ft_lstnew2(a, b, c, size));
}

void appand_exportorm(t_list **node,char *cont)
{
	if (cont)
	{
		(*node)->content = ft_strjoin((*node)->content, cont);
		if ((*node)->cont)
			(*node)->cont = ft_strjoin((*node)->cont, cont);
		else
		(*node)->cont = ft_strdup(cont);
	}
}

void appand_export(t_list *env,char *p)
{
	t_list	*tmp;
	char	*name;
	char	*cont;
    char *content;
	int		i;

	i = 0;
	tmp = env;
	while (p && p[i] && p[i] != '+')
		i++;
	name = ft_substr(p, 0, i);
	if (p + i + 2)
		cont = ft_strdup(p + i +2);
	else
		cont = NULL;
	while (tmp)
	{
		if (!ft_cmp(tmp->name, name))
		{
			appand_exportorm(&tmp, cont);
			return ;
		}
		tmp = tmp->next;
	}
     content =ft_join(name,p + i+ 1);
	ft_lstadd_back(&env, ft_lstnew2(content, name, cont, ft_lstsize(env)));
    sort_env(&env);
}

void exportwork(char *p, int flag, t_list *env)
{
	int		i;
	char	*name;
	char	*cont;

	i = 0;
	if (flag == 1)
		add_export(env, p, p, NULL);
	else if (flag == 2)
	{
		while (p && p[i] && p[i] != '=')
			i++;
		name = ft_substr(p, 0, i);
		if (p + i + 1)
			cont = ft_strdup(p + i +1);
		else
			cont = NULL;
		add_export(env, p, name, cont);
	}
	else if (flag == 3)
		appand_export(env, p);
}

