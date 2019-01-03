NAME	=	ft_ls

SRC		=	main.c util.c error.c ft_ls.c item.c print_basic.c recursion.c \
			sort.c format.c print_format.c invalid.c parse_input.c \
			file_dir.c time_sort.c long.c get_access.c

OBJ		=	$(SRC:.c=.o)

CFLAGS	=	-Wall -Wextra -Werror

$(NAME): $(OBJ)
	#@make -C libft/
	@gcc $(OBJ) -o $(NAME) -L libft/ -lft -fsanitize=address -g

all: $(NAME)

clean:
	@make -C libft/ clean
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME) $(OBJ)

re: fclean $(NAME)
