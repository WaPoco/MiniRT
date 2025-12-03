NAME=minilibx
CC=cc
CFLAGS=-Wall -Wextra -Werror
LFLAGS=-L./minilibx-linux -lmlx -lX11 -lXext -lm
HEADER=./Include/miniRT.h
SRCS=src/img.c src/main.c src/intersec.c src/vector_op.c src/color.c \
		src/camera.c src/matrix_op.c
OBJS=$(SRCS:.c=.o)

all: Libmlx $(NAME)

Libmlx:
	make -C ./minilibx-linux

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LFLAGS) -o $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all re Libmlx
