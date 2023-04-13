/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallaoui <mallaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 12:41:23 by mallaoui          #+#    #+#             */
/*   Updated: 2023/04/13 08:15:06 by mallaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*ft_lstnew2(void *content, char *name, char *cont, int i)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	if (content)
		new->content = content;
	else
	new->content = NULL;
	if (cont)
		new->cont = cont;
	else
		new->cont = NULL;
	if (name)
		new->name = name;
	else
		new->name = NULL;
	new->index = i;
	new->next = NULL;
	return (new);
}

void	fill_env2(t_list **env, int i)
{
	int		j;
	char	*cont;
	char	*content;
	char	*tmp;

	j = 0;
	while (environ[i][j] && environ[i][j] != '=')
				j++;
	tmp = ft_substr(environ[i], 0, j);
	if (environ[i] + j + 1)
		cont = ft_strdup(environ[i] + j + 1);
	else
		cont = NULL;
	content = ft_strdup(environ[i]);
	ft_lstadd_back(env, ft_lstnew2(content, tmp, cont, i));
}

void setdefault(t_list **env)
{
	char *content[3];
	char *cont[2];
	char *name[3];
	char pwd[1024];
	
	name[0] = ft_strdup("OLDOWD");
	content[0] =ft_strdup("OLDOWD");
	ft_lstadd_back(env,ft_lstnew2(content[0],name[0],NULL,0));
	getcwd(pwd,sizeof(pwd));
	name[1] = ft_strdup("PWD");
	content[1] =ft_join("PWD=",pwd);
	cont[0] = ft_strdup(pwd);
	ft_lstadd_back(env,ft_lstnew2(content[1],name[1],cont[0],1));
	name[2] = ft_strdup(" SHLVL");
	content[2] =ft_strdup("SHLVL=1");
	cont[1] = ft_strdup("1");
	ft_lstadd_back(env,ft_lstnew2(content[2],name[2],cont[1],2));
	
	
}

void	fill_env(t_list **env)
{
	int		i;
	int		j;
	char	*cont;
	char	*content;

	i = 0;
	*env = NULL;
	if(!environ[0])
	{
		setdefault(env);
		return ;
	}
	while (environ && environ[i])
	{
		j = 0;
		if (!ft_strncmp(environ[i], "OLDPWD", 6))
		{
			content = ft_strdup("OLDPWD");
			cont = ft_strdup("OLDPWD");
			ft_lstadd_back(env, ft_lstnew2(content, cont, NULL, i));
		}
		else
			fill_env2(env, i);
		i++;
	}
}
