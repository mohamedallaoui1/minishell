/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerraoui <aerraoui <marvin@42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 01:41:56 by aerraoui          #+#    #+#             */
/*   Updated: 2023/04/06 01:42:12 by aerraoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

int	ft_export2(int flag, t_list *env, char **p)
{
	int	i;
	int	j;

	i = 1;
	while (p[i])
	{
		j = ft_check_export(p[i]);
		if (j == 0)
		{
			ft_printf(2, "bash: export: `%s': not a valid identifier", p[i]);
			flag = 1;
			i++;
		}
		else
			exportwork(p[i++], j, env);
	}
	return (flag);
}