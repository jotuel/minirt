AR = ar rcs
CC = cc
TARGET_REPO = https://github.com/codam-coding-college/MLX42.git
INCLUDE_DIRS = libft
INCLUDE = Makefile
HEADER = declare.h minirt.h types.h
HEADERS	= -Iinclude -IMLX42/include/MLX42
CFLAGS = -Wall -Wextra -Werror -g2 -flto -O3 -ffast-math -march=native $(HEADERS)
MLX	= MLX42
LIBFT = libft/libft.a
LIBS = -L $(MLX)/build -lmlx42 -L libft -lft -ldl -lglfw -pthread -lm
SRC = minirt.c error.c color.c trace.c camera.c cylinder.c \
	sphere.c plane.c utils.c light.c shade.c hooks.c set.c \
	prerender.c rotate.c translate.c hook_utils.c
PARSE = file.c utils.c ambient.c light.c camera.c cylinder.c sphere.c plane.c
MATH = math.c lerp.c vector.c vector3.c vector_math.c vector3_math.c quat.c
HEADER := $(addprefix include/, $(HEADER))
SRC := $(addprefix src/, $(SRC)) $(addprefix src/parser/,\
	$(PARSE)) $(addprefix src/math/, $(MATH))
OBJ := $(SRC:%.c=%.o)
MAKE = make -C
NAME = miniRT

all: $(NAME) $(SRC) $(HEADER)
$(NAME): $(MLX) $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $@
%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<
$(LIBFT):
	$(MAKE) libft all supp bonus
$(MLX):
	git clone $(TARGET_REPO) $@
	cmake $(MLX) -B $(MLX)/build
	$(MAKE) $(MLX)/build -j4
clean:
	$(MAKE) libft clean
	rm -f $(OBJ)
fclean: clean
	$(MAKE) libft fclean
	rm -rf $(MLX)
	rm -f $(NAME)
re: clean all

.PHONY:
	all, libft, clean, flean, re, $(MLX)
