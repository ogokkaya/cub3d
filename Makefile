NAME = cub3d
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM	= rm -rf

SRC = 	src/main.c\
		src/malloc_collactor.c\
		src/path_control.c\
		inc/get_next_line/get_next_line.c\
		inc/get_next_line/get_next_line_utils.c


LIBFT_PATH = ./inc/libft/
LIBFT				=	$(LIBFT_PATH)/libft.a

OBJS				=	$(SRC:.c=.o)

all: 		$(NAME)

$(NAME):	$(OBJS)
			@make -C $(LIBFT_PATH)
			@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFT) 

clean:
			@$(RM) $(OBJS)
			@make fclean -C $(LIBFT_PATH)

fclean:		clean
			@$(RM) $(NAME)

re:			fclean all

.PHONY:		clean fclean re all