/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aerraoui <aerraoui <marvin@42.fr>>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 04:40:09 by aerraoui          #+#    #+#             */
/*   Updated: 2023/04/05 13:27:44 by aerraoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" 

t_list *getfile(char *p)
{
	DIR* dir;
	t_list *head;

	head = NULL;
	dir = opendir(".");
	if(!dir)
		return(0);
	struct dirent *entity;
	entity = readdir(dir); 
	while(entity)
	{
		if(check_wild(p,entity->d_name) != -1)
	ft_lstadd_back(&head,ft_lstnew(entity->d_name));
	entity = readdir(dir);
	}
	//closedir(dir);
	free(entity);
	return(head);

}

char *new_cmd(char *p, int i,t_list *file)
{
	int savei;
	int j;
	char *new;
	t_list *tmp;
	savei =i;
	j = 0;
	while(i !=0 && p[i] != ' ')
		i--;
	new = calloc(ft_strlen(p)+1,1);
	while(p && p[j] && j < i)
	{
		new[j] = p[j];
		j++;
	}
	if(i != 0)
		new[j++] = ' ';	
	if(file)
	{
		new = ft_strjoin(new,file->content);
			file=file->next;
		while(file)
		 {
			if (ft_strchr_normal(file->content, '$'))
			{
				new=ft_specequaot(new,file->content);
			}
			else
				new=ft_specejoin(new,file->content);
			tmp = file;
			file =file->next;
			free(tmp);
		}
		 while(p[savei] && p[savei] != ' ')
			savei++;
		new =ft_strjoin(new,(p + savei));
	}
	else
	{
		savei = j;
		while(p && p[j])
			new[j++] = p[savei++];
	}
	 return(new);
}

char *set_file(char *p,int i)
{
	int savei;
	int start;
	char *end;
	char *new;
	t_list *file;
	

	savei=i;
	while(i != 0 &&p[i] && p[i] != ' ')
		i--;
	if( i != 0)
		i++; 
	start =i;
	i =savei;
	while(p[i] && p[i] != ' ')
		i++;
	end = ft_substr(p,start,i-start);
	file = getfile(end);
	new = new_cmd(p,savei,file);
	return(free(p),free(end),new);
}

char *ft_wildcard(char *p)
{
	int i;
	char type;

	i = 0;
	while(p && p[i])
	{
		if (p[i] == '"' || p[i] == '\'')
		{
			type = p[i++];
			while (p[i] &&p[i] !=type)
				i++;
		}
		 if (p[i] == '*')
		{
			p = set_file(p,i);	
			if(p[i] == '*')
				i++;
			else 
				i = 0;
		}
		else
			i++;
	}
	return(p);
}