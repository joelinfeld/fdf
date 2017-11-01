NAME=fdf

#compiler flags
CC=gcc
CFLAGS=-Wall -Wextra -Werror

#fdf sources
SRCS = srcs/realmain.c
OBJS=$(SRCS:%.c=%.o)


#libft
LFT_DIR = libft
LFT_LINK = -L$(LFT_DIR) -lft

#minilibx
MLX_DIR = minilibx
MLX_LINK = -L$(MLX_DIR) -lmlx
INC = -I libft/includes -I minilibx -I includes

all: $(NAME)

$(NAME): $(OBJS)
	make -C $(LFT_DIR)
	make -C $(MLX_DIR)
	$(CC) $(CFLAGS) $(LFT_LINK) $(MLX_LINK) $(OBJS) -framework OpenGL -framework AppKit -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INC) -c -o $@ $^

clean:
	make -C $(LFT_DIR) clean
	make -C $(MLX_DIR) clean
	-rm -f $(OBJS)

fclean: clean
	make -C $(LFT_DIR) fclean
	-rm -f $(NAME)

re: fclean all
