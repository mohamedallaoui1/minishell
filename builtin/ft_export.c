/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallaoui <mallaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 12:40:45 by aerraoui          #+#    #+#             */
/*   Updated: 2023/04/10 04:06:38 by mallaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sort_env(t_list **env)
{
	int		tmp;
	t_list	*cournt;
	t_list	*next;

	cournt = *env;
	while (cournt)
	{
		next = *env;
		while (next)
		{
			if ((ft_cmp(cournt->content, next->content) > 0 && \
			cournt->index < next->index) || \
				(ft_cmp(cournt->content, next->content) <= 0 && \
				cournt->index >= next->index))
			{
				tmp = cournt->index;
				cournt->index = next->index;
				next->index = tmp;
			}
			next = next->next;
		}
		cournt = cournt->next;
	}
}

int	ft_sort(t_list *env)
{
	sort_env(&env);
	sort_env(&env);
	sort_env(&env);
	sort_env(&env);
	sort_env(&env);
	return (ft_lstsize(env));
}

void	afich_expoer(t_list *env)
{
	int		size;
	int		i;
	t_list	*tmp;

	i = 0;
	size = ft_sort(env);
	while (size)
	{
		tmp = env;
		while (tmp)
		{
			if (i == tmp->index)
			{
				printf("declare -x %s", tmp->name);
				if (tmp->cont)
					printf("=\"%s\"\n", tmp->cont);
				else
					printf("\n");
				i++;
				size--;
				break ;
			}
			tmp = tmp->next;
		}
	}
}

int	ft_check_export(char *p) 
{
	int	i;

	i = 0;
	if (ft_isdigit(p[0]) || p[0] == '=' || p[0] == '+')
		return (0);
	while (p && p[i])
	{
		if (!ft_isalnum(p[i]) && p[i] != '_')
			break ;
		i++;
	}
	if (!p[i])
		return (1);
	else if (p[i] == '=')
		return (2);
	else if (p[i] == '+' && p[i + 1] && p[i +1] == '=')
		return (3);
	else
		return (0);  
}

int ft_export(int fd, int check, char **p, t_list *env)
{
	t_list	*tmp;
	int		flag;

	flag = 0;
	tmp = env;
	glob.exit_status = 0;
	if (!p[1])
		afich_expoer(tmp);
	else
	{
		flag = ft_export2(flag, env, p);
		if (flag == 1)
			glob.exit_status = 1;
	}
	if (check)
		exit(0);
	return (ft_free(p), 0);
}