EXECUTION_SRC = main.c libft/ft_strlen.c libft/ft_strdup.c libft/ft_strjoin.c libft/ft_split.c count_lines.c moves.c map_handling.c ray_casting.c draw_cercle.c reading_map.c initialize_data.c parsing.c render_player.c mlx_funcs.c render_map.c cast.c cast_1.c mini_map_remain.c create_compass.c textures.c\
				rendring_walls.c mini_map.c update.c
BASIC_SRC = $(EXECUTION_SRC)

OBJ = ${BASIC_SRC:.c=.o}
CFLAG =  -g -fsanitize=address
# CFLAG = /*-Imlx*/ MLX -g 
# -Wall -Wextra -Werror# -g -fsanitize=address -Imlx
NAME = cub3D

CC = cc

all : ${NAME}

$(NAME): $(OBJ) 
		${CC} ${CFLAG} ${OBJ} -lmlx -framework OpenGL -framework AppKit -o ${NAME}

run: $(NAME)
	./$(NAME)

%.o: %.c
		@${CC} ${CFLAG} -I ./MLX -c $< -o $@

norm :
	@norminette

clean :
	@rm -rf ${OBJ}

fclean : clean
	@rm -rf ${NAME}

re : fclean all

.PHONY : clean norm
