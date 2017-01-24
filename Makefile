NAME = lem_in

SRC = main.c error.c init.c parse.c get.c tube.c util.c list.c check.c check_tube.c ants.c ft_strsplit_fn.c

OBJ = $(SRC:.c=.o)

FLAG = -Wall -Werror -Wextra

LIBFT = libft -lft

INCLUDES = -I libft/includes

.PHONY : libft.a

all: libft.a  $(NAME)

libft.a:
		@$(MAKE) -C ./libft

$(NAME): $(OBJ) 
		gcc $(FLAG) $(OBJ) $(INCLUDES) -L$(LIBFT) -o $(NAME)

%.o: %.c
		gcc $(FLAG) $(INCLUDES) -c $^

clean :
		@make clean -C ./libft
			rm -f $(OBJ)

fclean : clean
		rm -f ./libft/libft.a
		rm -f $(NAME)

re : fclean all
