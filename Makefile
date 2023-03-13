NAME = minishell
CC = cc
libft = libft/libft.a

SRC = ft_firstword.c ft_expand.c minishell.c split_pipe.c utils.c fill_struct.c string_handling.c checkerror.c ft_free.c  fiil_stract2.c

OBJ = $(SRC:.c=.o)

all: $(NAME)
$(NAME): $(OBJ)
	make bonus -C libft
	$(CC) $(OBJ) $(libft) -lreadline -fsanitize=address -o $(NAME) 

clean:
	rm -f $(OBJ)
	make clean -C libft

fclean: clean
	rm -f $(NAME)
	make fclean -C libft

re: fclean all