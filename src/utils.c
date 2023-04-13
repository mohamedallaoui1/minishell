/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallaoui <mallaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 21:10:11 by mallaoui          #+#    #+#             */
/*   Updated: 2023/04/13 23:30:20 by mallaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*fix_buffer_v2(char *buffer)
{
	int		i;
	int		j;
	int		len;
	char	*new_string;

	i = 0;
	j = 0;
	len = ft_strlen(buffer);
	new_string = ft_calloc(len * 2, 1);
	while (buffer[i])
	{
		if (buffer[i] == '"')
		{
			new_string[j++] = buffer[i++];
			while (buffer[i] && buffer[i] != '"')
				new_string[j++] = buffer[i++];
			new_string[j++] = buffer[i++];
		}
		if (buffer[i] == ' ')
			while (buffer[i] && (buffer[i + 1] == ' '))
				i++;
		new_string[j++] = buffer[i++];
	}
	new_string[j] = '\0';
	free(buffer);
	return (new_string);
}

void	fix_buffer_norm(char *buffer, char **new_string, \
unsigned int len, unsigned int **arr)
{
	if (buffer[(*arr)[0]] == '>' && buffer[(*arr)[0] + 1] == \
	'>' && buffer[(*arr)[0] - 1] == ' ')
		(*new_string)[(*arr)[1]++] = buffer[(*arr)[0]++];
	if ((*arr)[0] > 0 && buffer[(*arr)[0]] == '<' && \
	buffer[(*arr)[0] + 1] == '<' && buffer[(*arr)[0] - 1] == ' ')
		(*new_string)[(*arr)[1]++] = buffer[(*arr)[0]++];
	if ((*arr)[0] > 0 && buffer[(*arr)[0] - 1] != ' ' && \
	buffer[(*arr)[0] - 1] != '<' \
	&& buffer[(*arr)[0] - 1] != '>')
		(*new_string)[(*arr)[1]++] = ' ';
	(*new_string)[(*arr)[1]++] = buffer[(*arr)[0]++];
	if ((*arr)[0] < len && buffer[(*arr)[0]] != ' ' && buffer[(*arr)[0]] != '<'
		&& buffer[(*arr)[0]] != '>')
	(*new_string)[(*arr)[1]++] = ' ';
}

char	*fix_buffer(char *buffer)
{
	unsigned int	len;
	char			*new_string;
	unsigned int	*arr;

	len = ft_strlen(buffer);
	new_string = malloc(len * 5);
	arr = malloc(sizeof(unsigned int) * 2);
	arr[0] = 0;
	arr[1] = 0;
	while (arr[0] < len)
	{
		if (buffer[arr[0]] == '"')
		{
			new_string[arr[1]++] = buffer[arr[0]++];
			while (arr[0] < len && buffer[arr[0]] != '"')
				new_string[arr[1]++] = buffer[arr[0]++];
			new_string[arr[1]++] = buffer[arr[0]++];
		}
		else if (buffer[arr[0]] == '<' || buffer[arr[0]] == '>')
			fix_buffer_norm(buffer, &new_string, len, &arr);
		else
			new_string[arr[1]++] = buffer[arr[0]++];
	}
	return (new_string[arr[1]] = '\0', free(buffer), free(arr), new_string);
}

void	free_all(t_all1 **all)
{
	t_all1	*tmp;
	t_file1	*tmpfile;

	tmp = (*all);
	while (tmp)
	{
		free(tmp->cmd);
		while (tmp->file)
		{
			tmpfile = tmp->file;
			if (tmpfile->type == HER)
				free(tmpfile->limiter);
			if (tmpfile->file)
				free(tmpfile->file);
			tmp->file = tmp->file->next;
			free(tmpfile);
			tmpfile = tmp->file;
		}
		free(tmp->file);
		(*all) = (*all)->next;
		free(tmp);
		tmp = (*all);
	}
}

void	ft_free1(char **p)
{
	int	i;

	i = 0;
	while (p[i] != 0)
	{
		free(p[i]);
		i++;
	}
	free(p);
}
