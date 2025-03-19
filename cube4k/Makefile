CC = cc

PURPLE = \033[35m
RED = \033[31m
CYAN = \033[36m
GREEN = \033[32m
RESET = \033[0m
BOLD = \033[1m

HEADERS_DIR = ./headers
SRC_DIR = ./src
OBJ_DIR = ./obj

CFLAGS = -g -fsanitize=address #-Wall -Wextra -Werror 
HFLAGS = -I$(HEADERS_DIR)

NAME = cub3D

HEADERS =  $(HEADERS_DIR)/cub3d.h
SOURCES =  $(SRC_DIR)/00_initialization/00_initialization.c \
           $(SRC_DIR)/01_parsing/parsing_map_colors.c \
           $(SRC_DIR)/01_parsing/parsing_map.c \
           $(SRC_DIR)/01_parsing/parsing_map_utils.c \
           $(SRC_DIR)/01_parsing/parsing_map_validation_utils.c \
           $(SRC_DIR)/01_parsing/parsing_map_validation.c \
           $(SRC_DIR)/01_parsing/parsing_map_textures.c \
           $(SRC_DIR)/01_parsing/parser_utils.c \
           $(SRC_DIR)/01_parsing/parser.c \
           $(SRC_DIR)/06_utils/library1.c \
           $(SRC_DIR)/06_utils/library2.c \
           $(SRC_DIR)/06_utils/library3.c \
           $(SRC_DIR)/06_utils/library4.c \
           $(SRC_DIR)/06_utils/split.c \
           $(SRC_DIR)/06_utils/splitTwo.c \
           $(SRC_DIR)/06_utils/printing_utils.c \
           $(SRC_DIR)/06_utils/file_utils.c \
           $(SRC_DIR)/06_utils/memory_utils.c \
           $(SRC_DIR)/06_utils/list_utils.c \
           $(SRC_DIR)/06_utils/get_next_line.c \
           $(SRC_DIR)/main.c

OBJS = $(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: banner $(NAME)

banner:
	@printf "$(PURPLE)$(BOLD)"
	@printf "\n"
	@printf "\t\t\t\t ██████╗██╗   ██╗██████╗ ██████╗ ██████╗ \n"
	@printf "\t\t\t\t██╔════╝██║   ██║██╔══██╗╚════██╗██╔══██╗\n"
	@printf "\t\t\t\t██║     ██║   ██║██████╔╝ █████╔╝██║  ██║\n"
	@printf "\t\t\t\t██║     ██║   ██║██╔══██╗ ╚═══██╗██║  ██║\n"
	@printf "\t\t\t\t╚██████╗╚██████╔╝██████╔╝██████╔╝██████╔╝\n"
	@printf "\t\t\t\t ╚═════╝ ╚═════╝ ╚═════╝ ╚═════╝ ╚═════╝💀\n"
	@printf "$(RESET)"

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -o $@ $(OBJS)
	@printf "$(GREEN)Compiled Successfully 🦈$(RESET)\n"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c -o $@ $<

clean: banner
	@rm -rf $(OBJ_DIR)
	@printf "$(CYAN)Cleaned object files 😈$(RESET)\n"

fclean: banner clean
	@rm -f $(NAME)
	@printf "$(RED)Cleaned executable 💀$(RESET)\n"

re: fclean all

.PHONY: clean fclean re banner
