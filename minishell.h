/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mallaoui <mallaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 16:53:15 by aerraoui          #+#    #+#             */
/*   Updated: 2023/04/13 22:21:13 by mallaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H 
extern char **environ;

#define HER 2
#define OUT 0
#define INF 1
#define APP 3

# include <termios.h>
# include "readline/readline.h"
# include <stdlib.h>
# include "libft/libft.h"
# include <readline/history.h>
# include "line/get_next_line.h"
# include "signal.h"
# include <dirent.h>
# include "ft_dprintf/ft_printf.h"

typedef struct s_glbl
{
    int     exit_status;
    int     check_sig;
    struct termios old_attr;
    struct termios new_attr;
    struct termios reset_attr;
}       t_glbl;

typedef struct s_fila
{
    char *file;
    char *limiter;
    int type;
    struct s_fila *next;
}           t_file1;

typedef struct s_all1
{
    int index;
    char *cmd;
    t_file1 *file;
    int    A;
    struct s_all1 *next;
}       t_all1;

typedef struct s_dup
{
    int infile;
    int outfile;
}               t_dup;

typedef struct s_exec
{
    int i;
    int in;
    int out;
    int fd[2];
    int sec_fd[2];
    int id;
    char *path;
    char **splited;
    int infile_fd;
    int outfile_fd;
    t_list  *env;
    t_dup   *duppin;
    char    **double_env;
    char **full_cmd;
    int    status;
}        t_exec;

typedef struct s_everything
{
    char **p;
	char *buffer;
	t_list *env;
	t_all1 *all;
	t_all1 *tmp;
	t_file1 *file;
	t_exec *vars;
	char *buff;
}       t_everything;

typedef struct s_expn
{
    int		i;
	int		j;
	char	*new;
	char	*s;
	int		size;
	int		**arr;
}       t_expnd;

t_glbl  glob;

void    rl_replace_line(char *str, int  clear);
char    **split_pipe(char *buff);
void    skip_spaces(char *p, int *i);
void    fill_struct2(char **p, t_all1   **all);
int    check_quotes(char *p);
int ft_eroro(char *buff);
char *ft_firstword(char *p);
void    fill_env(t_list **env);
void	ft_free(char **p);
char *expand(t_list *env, char *p);
void expandfile(t_list *env,t_file1 *file);
void open_here_doc(t_all1  **all,t_list *env);
int	ft_cmp(const char *s1, const char *s2);
char	*ft_specejoin(char *s1, char *s2);
 char *ft_wildcard(char *p);
 char	*ft_specequaot(char *s1, char *s2);
 int check_wild(char *card,char *file);
 int ft_cd(int fd,int check ,char **p,t_list *env);
 int ft_pwd(int fd,int check ,char **p,t_list *env);
 int ft_exit(int fd,int check ,char **p,t_list *env);
 int ft_env(int fd,int check ,char **p,t_list *env);
 int ft_echo(int fd,int check ,char **p,t_list *env);
 int ft_unset(int fd,int check ,char **p,t_list *env);
 int ft_export(int fd,int check ,char **p,t_list *env);
 void	join_and_check_if_excutable(t_exec *vars, t_all1 *all);
 void    execution(t_all1 *all, t_exec **vars, t_list *env);
 char *delete_qouats(char *p);
 void destroy_qoute(char **p);
 int     ft_tablen(char **p);
 int is_built_in(char *p);
void    check_built_ins(int fd, int check, char **p, t_exec *vars);
t_list	*ft_lstnew2(void *content, char *name, char *cont, int i);
int ft_export(int fd, int check, char **p, t_list *env);
void	add_export_norm(t_list **node, char *name, char *cont);
void	add_export(t_list *env, char *content, char *name, char *cont);
void appand_exportorm(t_list **node,char *cont);
void appand_export(t_list *env,char *p);
void exportwork(char *p, int flag, t_list *env);
int	ft_export2(int flag, t_list *env, char **p);
void	sort_env(t_list **env);
int	ft_check_export(char *p);
void    handle_1(int signum);
void    handle_2(int signum);
int check_ambiguous(t_file1 **file, t_list *env);
/*       mn hnaaaaaa             */
void	execute(t_exec **vars, t_all1 *all);
void	middle(t_exec **vars, t_all1 *all);
void	last(t_exec **vars, t_all1 *all);
void	first(t_exec **vars, t_all1 *all);
int	only_white_spaces(char *str);
int	is_built_in(char *p);
void	check_built_ins(int fd, int check, char **p, t_exec *vars);
void	indexing(t_all1 **all);
int    open_files(t_exec **vars, t_file1 *file, int check);
void	init_struct(t_exec **vars, t_list *env);
void	free_everything(t_exec *vars);
void	search_and_check(t_exec *vars);
char	*get_content(t_list *env, char *p);
void	mini_expand(char **p, char **new, t_list *env, t_expnd *vars);
int	mini_ex_part2(char **p, char **new, t_expnd **vars, t_list *env);
void	part2_child_hhhh(char **p, char **new, t_expnd **vars);
int	mini_ex_part1(char **p, char **new, t_expnd **vars);
char	*ft_strdupx(char *s1);
void	fill_content(char **new, char *cont, int *i);
int	count_total(t_list *env, char *p);
void	count_total_while(char *p, int *i, int *cont_size, t_list *env);
void	norm_count_total_1(char *p, int	*i, int	*cont_size, t_list *env);
int	norm_2(char *p, int *i, int *cont_size, t_list *env);
int	norm_1(char *p, int *i, int *cont_size);
void	find_token(t_all1 **all, t_file1 **file, int i);
char	*heredoc_name(int i);
void	find_file(t_all1 **all, t_file1 **file, int i, int j);
char	*delete_file(t_all1 **all, t_file1 *file, int i);
void	delete_file_norm(int *size, int *i, int *x);
void	fix_buffer_norm(char *buffer, char **new_string, unsigned int len, unsigned int **arr);
char	*fix_buffer(char *buffer);
void	free_all(t_all1 **all);
void	ft_free1(char **p);
char	*fix_buffer_v2(char *buffer);
void	reinitialize(t_everything **shell);
void	free_everything_shell(t_everything **shell);
void	get_attr(void);
void	free_struct(t_all1 **all);
void	handle(int signum);
void	initialize(t_all1 **all);
char	*delet_speace(char *p);









#endif