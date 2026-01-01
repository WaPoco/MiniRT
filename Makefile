NAME = miniRT
CC = cc
CFLAGS = -Wall -Wextra -Werror -g

LIBMLX = ./minilibx-linux/libmlx.a
LIBFT  = ./libft/libft.a

LFLAGS = -L./minilibx-linux -lmlx -lX11 -lXext -lm \
         -L./libft -lft

HEADER = ./Include/miniRT.h ./Include/Libft.h ./Include/minilibx-linux/mlx.h ./Include/get_next_line/get_next_line.h

SRCS = src/parser.c src/color.c src/matrix_op.c src/init.c \
       src/camera.c src/parse_objects2.c src/parse_double.c \
       src/free.c src/img.c src/events.c src/parse_objects1.c \
       src/main.c src/intersec.c src/object.c src/vector_op3.c \
       src/vector_op2.c src/render.c src/vector_op1.c \
       src/parse_tools.c src/det.c get_next_line/get_next_line.c \
	   get_next_line/get_next_line_utils.c

OBJS = $(SRCS:.c=.o)

all: Libmlx Libft $(NAME)

Libmlx:
	$(MAKE) -C ./minilibx-linux

Libft:
	$(MAKE) -C ./libft

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LFLAGS) -o $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	$(MAKE) clean -C ./libft
	$(MAKE) clean -C ./minilibx-linux

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C ./libft

re: fclean all

.PHONY: clean fclean all re Libmlx Libft

