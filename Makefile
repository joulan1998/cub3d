EXECUTION_SRC = main.c libft/ft_strlen.c libft/ft_strdup.c libft/ft_strjoin.c libft/ft_split.c count_lines.c moves.c map_handling.c ray_casting.c
BASIC_SRC = $(EXECUTION_SRC)

OBJ = ${BASIC_SRC:.c=.o}
CFLAG = -I ./minilibx-linux -g
# -Wall -Wextra -Werror# -g -fsanitize=address -Imlx
NAME = cub

CC = cc

all : ${NAME}

$(NAME): $(OBJ) 
		${CC} ${CFLAG} ${OBJ} -lmlx -framework OpenGL -framework AppKit -o ${NAME}
#${CC} ${CFLAG} ${OBJ} -L ${READLINE_L} -o ${NAME} -lreadline


%.o: %.c
		@${CC} ${CFLAG} -c $< -o $@

norm :
	@norminette

clean :
	@rm -rf ${OBJ}

fclean : clean
	@rm -rf ${NAME}

re : fclean all

.PHONY : clean norm
