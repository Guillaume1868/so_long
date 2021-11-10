NAME 	=	SoLong

SRC		=	so_long.c get_next_line.c get_next_line_utils.c load.c map.c \
			movement.c end.c map2.c

OBJ		=	$(SRC:.c=.o)

CC		=	gcc

RM		=	rm -f

GREEN       =   \e[38;5;118m
YELLOW      =   \e[38;5;226m
RESET       =   \e[0m
_SUCCESS    =   [$(GREEN)SUCCESS$(RESET)]
_INFO       =   [$(YELLOW)INFO$(RESET)]

all:	$(NAME)


%.o: %.c
	@$(CC) -Wall -Wextra -Werror -Imlx -c $< -o $@
	@printf "$(_INFO) OBJ $@ compiled.\n"

$(NAME): $(LIBFT) $(OBJ)
	@$(MAKE) -C  ./mlx
	@$(MAKE) -C  ./libft
	@$(CC) -g $(OBJ) -Llibft -lft -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)
	@printf "$(_SUCCESS) SoLong ready.\n"

clean:
	@ $(RM) $(OBJ)
	@printf "$(_INFO) OBJ removed.\n"

fclean: clean
	@ $(MAKE) clean -C mlx
	@ $(MAKE) fclean -C libft
	@ $(RM) $(NAME)
	@printf "$(_INFO) $(NAME) removed.\n"

re: fclean all

.PHONY: all clean fclean re
