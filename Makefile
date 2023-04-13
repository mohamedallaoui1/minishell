NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
libft = libft/libft.a

SRC = ft_firstword.c ft_specejoine.c Parsing/Expand/ft_expand.c Parsing/Expand/utils.c	Parsing/Expand/utils1.c check_wild.c src/utils.c src/minishell.c \
fill_struct.c string_handling.c checkerror.c ft_free.c  Parsing/fill_struct/fiil_stract2.c Parsing/fill_struct/utils.c Parsing/fill_struct/utils1.c wildcard.c line/get_next_line.c\
ft_dprintf/lib/ft_itoa.c ft_dprintf/lib/ft_strlen.c ft_dprintf/lib/ft_putnbr.c ft_dprintf/lib/ft_putchar.c ft_dprintf/lib/ft_puthexa.c ft_dprintf/lib/ft_putstr.c ft_dprintf/lib/ft_putadd.c\
ft_dprintf/lib/ft_putuns.c ft_dprintf/ft_printf.c\
line/get_next_line_utils.c read_here_doc.c ft_cmp.c	Execution/execute.c Execution/utils.c ft_quoatjoin.c\
builtin/ft_cd.c builtin/ft_pwd.c builtin/ft_exit.c builtin/ft_env.c builtin/ft_echo.c builtin/ft_unset.c builtin/ft_export.c\
builtin/ft_export2.c builtin/utils.c ft_ambiguous.c Execution/execute1.c Execution/utils1.c Execution/open_files.c Execution/utils3.c\

OBJ = $(SRC:.c=.o)

all: $(NAME)
$(NAME): $(OBJ)
	make bonus -C libft
	gcc $(OBJ) $(libft) -o $(NAME) -fsanitize=address -lreadline -L /Users/${USER}/Desktop/readline -I /Users/${USER}/Desktop/readline -lcurses

clean:
	rm -f $(OBJ)
	make clean -C libft

fclean: clean
	rm -f $(NAME)
	make fclean -C libft

re: fclean all
