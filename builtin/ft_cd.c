/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerraoui <aerraoui <marvin@42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 13:58:13 by aerraoui          #+#    #+#             */
/*   Updated: 2023/04/12 23:17:00 by aerraoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

char	*gethome(t_list *env)
{
	char	*p;

	while (env)
	{
		if (ft_cmp(env->name, "HOME") == 0)
		{
			p = ft_strdup(env->cont);
			return (p);
		}
		env = env->next;
	}
	return (0);
}

char	*getold(t_list *env)
{
	while (env)
	{
		if (!ft_cmp("OLDPWD", env->name))
			return (env->cont);
		env = env->next;
	}
	return (NULL);
}

int ft_changedir(t_list **env, char *new, char*old)
{
	t_list	*head;
	int		i;
	char	pwd[1024];

	head = *env;
	i = chdir(new);
	while (head)
	{
		if (!ft_cmp(head->name, "PWD") && i != -1)
		{
			getcwd(pwd, sizeof(pwd));
			if (head->cont)
			{
				free(head->cont);
				free(head->content);
			}
			head->cont = ft_strdup(pwd);
			head->content = ft_join("PWD=", pwd);
		}
		else if (!ft_cmp(head->name, "OLDPWD") && i != -1)
		{
			if (head->cont)
				free(head->cont);
			free(head->content);
			head->cont = ft_strdup(old);
			head->content = ft_join("OLDPWD=", old);
		}
		head = head->next;
	}
	return (i);
}

int cdwork(int fd, char *p, char *home, t_list **env)
{
	int		i;
	char	pwd[1024];
	char	*s;

	getcwd(pwd, sizeof(pwd));
	s = getold(*env);
	if (ft_cmp(p, "-") == 0)
	{
		if (!s)
		{
			ft_printf(2, "bash: cd: OLDPWD not set\n");
			glob.exit_status = 1;
		}
		else
		{
			i = ft_changedir(env, s, pwd);
			getcwd(pwd, sizeof(pwd));
			ft_printf(fd, "%s\n", pwd);
		}
	}
	else if (ft_cmp(p, "~") == 0)
	{
		i = -2;
		if (home)
			i = ft_changedir(env, home, pwd);
		else
			ft_printf(2, "bash: cd: HOME not set\n");
	}
	else
		i = ft_changedir(env, p, pwd);
	return (i);
}

int ft_cd(int fd, int check, char **p,t_list *env)
{
	int		i;
	char	*home;
	char	pwd[1024];

	getcwd(pwd, sizeof(pwd));
	home = gethome(env);
	if (p[1] != NULL)
		i = cdwork(fd, p[1], home, &env);
	else
	{
		if (home)
			i = ft_changedir(&env, home, pwd);
		else
		{
			ft_printf(2, "bash: cd: HOME not set\n");
			glob.exit_status = 1;
			if (check)
				exit(glob.exit_status);
			else
				return (ft_free(p), 1);
		}
	}
	if (i == -1 || i == -2)
	{
		if(i == -1)
			perror("bash: cd :");
		glob.exit_status = 1;
	}
	free(home);
	if (check)
		exit(glob.exit_status);
	else
		return (ft_free(p), 0);
}
