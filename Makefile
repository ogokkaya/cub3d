NAME = cub3d
CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address
RM	= rm -rf

SRC = 	src/main.c\
		src/malloc_collactor.c\
		src/path_control.c\
		inc/get_next_line/get_next_line.c\
		inc/get_next_line/get_next_line_utils.c \
		src/raycast.c \
		src/key_hook.c \
		src/map.c \
		src/draw.c
MLX = -Lmlx -lmlx -framework OpenGL -framework AppKit
LIBFT_PATH = ./inc/libft/
LIBFT				=	$(LIBFT_PATH)/libft.a

OBJS				=	$(SRC:.c=.o)

all: 		$(NAME)

$(NAME):	$(OBJS)
			@make -C $(LIBFT_PATH)
			@make -C mlx/
#			$(CC) $(OBJ) -Lmlx -lmlx -L/usr/lib -Imlx -lXext -lX11 -lm -lz -o $(NAME)
			@$(CC) $(CFLAGS) $(OBJS) $(MLX) -o $(NAME) $(LIBFT) 

clean:
			@$(RM) $(OBJS)
			@make fclean -C $(LIBFT_PATH)

fclean:		clean
			@$(RM) $(NAME)

re:			fclean all

.PHONY:		clean fclean re all