EXECUTION_SRC = main.c libft/ft_strlen.c libft/ft_strdup.c libft/ft_strjoin.c count_lines.c moves.c map_handling.c ray_casting.c draw_cercle.c initialize_data.c parsing.c render_player.c mlx_funcs.c render_map.c cast.c cast_1.c mini_map_remain.c create_compass.c textures.c cast_2.c\
				rendring_walls.c mini_map.c update.c\
				parser.c parser_utils.c parsing_map.c parsing_map_colors.c parsing_map_textures.c parsing_map_utils.c parsing_map_validation.c parsing_map_validation_utils.c 00_initialization.c\
				file_utils.c get_next_line.c library1.c library2.c library3.c library4.c list_utils.c memory_utils.c printing_utils.c split.c splitTwo.c

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
