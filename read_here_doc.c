
#include "minishell.h"

char *delete_qouats(char *p)
{
	int i ;
	int j;
	char *new;
	char type;

	i = 0;
	j = 0 ;
	new = calloc(ft_strlen(p)+1,1);
	while(p && p[i])
	{
		if(p[i] == '\'' || p[i] == '"')
		{
			type = p[i];
			i++;
			while(p  && p[i] != type)
			{
				new[j++] = p[i++]; 
			}
			i++;
		}
		else
			new[j++] = p[i++];
	}
	new[j] = '\0';
	free(p);
	return(new);
}

int is_expandad(char *p)
{
	int i;

	i = 0;

	while (p && p[i])
	{
	   if(p[i] == '\'' || p[i] == '"')
			return(0);
		i++;
	}
	return(1);
}

void read_here_doc(t_file1 **file,t_list *env)
{
	int fd ;
	int exp ;
	char *line;
	char *limiter;


	exp = is_expandad((*file)->limiter);
	(*file)->limiter = delete_qouats((*file)->limiter);
	limiter = ft_strdup((*file)->limiter);
	limiter = ft_strjoin(limiter, "\n");
	fd = open((*file)->file, O_CREAT | O_RDWR | O_TRUNC,0644);
	write(1, "> ", 2);
	line = get_next_line(0);
	while(line)
	{
		if(!line || ft_cmp(line, limiter)==0 )
		{
			free(line);
			break ;
		}
		if(exp)
			line = expand(env, line);
		write(fd,line,ft_strlen(line));
		free(line);
		write(1, "> ", 2);
		line = get_next_line(0);
	}
	glob.exit_status = 0;
	free(limiter);
	exit(glob.exit_status);
}

void    handler(int signum)
{
	glob.exit_status = 1;
	exit(glob.exit_status);
}

void open_here_doc(t_file1 **sile,t_list *env)
{
	int id;
	int fd;
	t_file1 *file ;
	int status;

	file = *sile;
	while(file)
	{
		if(file->type == HER)
		{
			id = fork();
			if (id == 0)
			{
				signal(SIGINT, handler);
				read_here_doc(&file, env);
			}
			else
			{
				signal(SIGINT, handle_1);
                waitpid(id, &status, 0);
			}
			file = file->next;
		}
		else
			file = file->next;
	}
}