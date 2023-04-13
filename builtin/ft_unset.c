/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerraoui <aerraoui <marvin@42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 00:57:10 by aerraoui          #+#    #+#             */
/*   Updated: 2023/04/13 04:36:24 by aerraoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstdelone1(t_list *lst, void (*del)(void *))
{
	if (lst && del)
	{
		del(lst->content);
		del(lst->name);
		if (lst->cont)
			del(lst->cont);
		free(lst);
	}
}

int	checker(char *p)
{
	int	i;

	i = 0;
	if (!p[0] || (p[0] >= '0' && p[0] <= '9'))
		return (0);
	while (p && p[i])
	{
		if (!ft_isalnum(p[i]) && p[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	delet_node(char *p,t_list **env)
{
	t_list	*prec;
	t_list	*cournt;

	if(ft_cmp(p, "_"))
	{
		cournt = *env;
		if (!ft_cmp(p, cournt->name))
		{
			prec = cournt;
			cournt = cournt->next;
			ft_lstdelone1(prec, free);
			return ;
		}
		prec = cournt;
		cournt = cournt->next;
		while (cournt)
		{
			if (!ft_cmp(p, cournt->name))
			{
				prec->next = cournt->next;
				ft_lstdelone1(cournt, free);
				return ;
			}
			prec = cournt;
			cournt = cournt->next;
		}
	}
}

void	set_index(t_list **env)
{
	t_list	*tmp;
	int		i;

	tmp = *env;
	i = 0;
	while (tmp)
	{
		tmp->index = i;
		i++;
		tmp = tmp->next;
	}
}

int	ft_unset2(char **p, t_list *env)
{
	int		i;
	int		flag;
	t_list	*tmp;

	i = 1;
	flag = 0;
	while (p && p[i])
	{
		tmp = env;
		if (!checker(p[i]))
		{
			ft_printf(2, "bash: unset:  `%s': not a valid identifier\n", p[i]);
			flag = 1;
		}
		else
			delet_node(p[i], &tmp);
		i++;
	}
	return (flag);
}

int	ft_unset(int fd, int check, char **p, t_list *env)
{
	int	flag;

	flag = 0;
	flag = ft_unset2(p, env);

	if (flag)
		glob.exit_status = 1;
	set_index(&env);
	if (check)
		exit(glob.exit_status);
	return (ft_free(p), glob.exit_status);
}
