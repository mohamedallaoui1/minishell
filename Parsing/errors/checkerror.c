/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkerror.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallaoui <mallaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 23:12:12 by aerraoui          #+#    #+#             */
/*   Updated: 2023/04/14 01:01:21 by mallaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	number_here(char *buff)
{
	int	i;
	int	count ;

	count = 0;
	i = 0;
	while (buff[i])
	{
		if (buff[i] == '<' && buff[i + 1] == '<')
		{
			count++;
			i += 2;
		}
		else
			i++;
	}
	if (count > 15)
	{
		printf("minishell: maximum here-document count exceeded\n");
		exit(2);
	}
	else
		return (1);
}
int ft_eroro(char *buff)
{
	if (!check_token1(buff) || !check_token2(buff))
	{
		printf("syntax error near unexpected token `>' or `<'\n");
		return (0);
	}
	if (!check_token0(buff))
	{
		printf("syntax error near unexpected token `newline\n");
		return (0);
	}
	if (!number_here(buff))
		return (0);
	return (1);
}
int ft_eroro(char *buff)
{
	int	i;
	int	c;

	if (syntaxeror(buff) == -1)
		return (0);
	c = ft_check_erorr(buff);
	if (c == 0)
		return (0);
	i = check_quotes(buff);
	if (!i)
	{
		printf("error in number of \" or '\n");
		return (0);
	}
	if (ft_eroro(buff) == 0)
		return (0);
	return (1);
}

