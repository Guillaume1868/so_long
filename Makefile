NAME 	=	SoLong

SRC		=	so_long.c

OBJ		=	$(SRC:.c=.o)

CC		=	gcc

RM		=	rm -f

GREEN       =   \e[38;5;118m
YELLOW      =   \e[38;5;226m
RESET       =   \e[0m
_SUCCESS    =   [$(GREEN)SUCCESS$(RESET)]
_INFO       =   [$(YELLOW)INFO$(RESET)]

all:	$(LFT) $(NAME)
	

%.o: %.c 
	$(CC) -Wall -Wextra -Werror -Imlx -c $< -o $@

$(LFT):
	@ $(MAKE) -C ./libft
$(NAME): $(LFT) $(OBJ) 
	$(MAKE) -C  ./mlx
	$(CC) $(OBJ) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)
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
