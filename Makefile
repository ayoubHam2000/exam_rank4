FILES = \
	microshell.c

OBJ_DIR = _OUT/

OBJ = $(addprefix $(OBJ_DIR), $(FILES:.c=.o))

NAME = microshell.out

all: $(NAME)

$(NAME): $(OBJ)
	gcc $(OBJ) -o $(NAME)

$(OBJ): $(OBJ_DIR)%.o : %.c
	mkdir -p $(dir $@)
	gcc -c $(@:$(OBJ_DIR)%.o=%.c) -o $@

clean:
	rm -rf $(OBJ_DIR)
	
fclean: clean
	rm -rf $(NAME)

re: fclean all
