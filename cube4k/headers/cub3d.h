#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>      
# include <unistd.h>  
# include <math.h> 
# include <stdbool.h>
# include <fcntl.h>

# define VALID_MAP_CHARS "01NSEW \n"
# define MAP_CONTENT_CHARS "01NSEW"
# define VALID_PLAYER_POSITION "NSEW"
# define INVALID_NBR_ARGS "Error: Invalid number of arguments\n"
# define MALLOC_ERROR "Error: Memory allocation failed\n"
# define INVALID_PATH "Error: Invalid path"
# define INVALID_FILE_EXTENSION "Error: Invalid file extension"
# define PARSING_ERROR "Error: Parsing failed"
# define OPEN_ERROR "Error: Could not open file\n"
# define SPLIT_FAILED ": Split failed\n"
# define MISSING_PARAMS ": Missing parameters\n"
# define RGB_ERROR ": Invalid RGB values"
# define INVALID_CHARACTER ": Invalid character in map\n"
# define INVALID_MAP "Invalid map"
# define INVALID_PLAYER "Invalid player"
# define MULTIPLE_PLAYERS "Multiple players found"
# define INVALID_MAP_BORDERS "Invalid map borders"
# define INVALID_MAP_CONTENT "Invalid map content"
# define MAP_ORDER_ERROR "Parameters are missing or the map elements aren't in order"
# define DUPLICATED_PARAM "Error: Duplicated Parameter"
/**
 * @struct s_tracker
 * @brief A structure to track various states and flags in the cub3d project.
 * 
 * This structure contains multiple boolean flags used to track the presence
 * and status of different elements in the cub3d project, such as textures,
 * floor and ceiling colors, and map parsing states.
 * 
 * @var s_tracker::no_tracker
 * Flag to track the presence of the north texture.
 * 
 * @var s_tracker::so_tracker
 * Flag to track the presence of the south texture.
 * 
 * @var s_tracker::we_tracker
 * Flag to track the presence of the west texture.
 * 
 * @var s_tracker::ea_tracker
 * Flag to track the presence of the east texture.
 * 
 * @var s_tracker::floor_tracker
 * Flag to track the presence of the floor color.
 * 
 * @var s_tracker::ceiling_tracker
 * Flag to track the presence of the ceiling color.
 * 
 * @var s_tracker::i
 * General purpose flag i.
 * 
 * @var s_tracker::j
 * General purpose flag j.
 * 
 * @var s_tracker::n
 * General purpose flag n.
 * 
 * @var s_tracker::s
 * General purpose flag s.
 * 
 * @var s_tracker::e
 * General purpose flag e.
 * 
 * @var s_tracker::w
 * General purpose flag w.
 * 
 * @var s_tracker::found_the_map
 * Flag to indicate if the map has been found.
 * 
 * @var s_tracker::found_empty_line
 * Flag to indicate if a new line has been found.
 */
typedef struct s_tracker 
{
	bool no_tracker;
	bool so_tracker;
	bool we_tracker;
	bool ea_tracker;
	bool floor_tracker;
	bool ceiling_tracker;
	bool found_the_map;
	bool found_the_player;
	bool found_empty_line;
} t_tracker;

typedef struct s_params
{
	char	**map;
	char	*no_texture;
	char	*so_texture;
	char	*we_texture;
	char	*ea_texture;
	int		floor_color;
	int		ceiling_color;
	size_t	map_width;
	size_t	map_height;
	// int p_x;
	// int p_y;
} t_params;

typedef struct s_map
{
	char			*line;
	struct s_map	*next;
} t_map;

// * 00 initialization functions
void	init_params(t_params *params);

// * 01 parsing functions
bool check_if_empty_line(char *line);
bool check_if_valid(t_tracker *tracker, char *line);
int parse_color(char **splited_line);
bool parse_map_line(char *line, t_map **map, t_tracker *tmp, t_params *params);
bool	parse_file_line(char *line, t_tracker *tmp, t_params *params);
bool extract_cleaned_map(t_params *params, t_map **map);
bool    parser(t_params *params, char *map_file);


// * 06 utils functions
// * file utils
bool is_valid_file_extension(const char *file_path, const char *extension);
bool is_valid_path(const char *path);
// * printing utils
void    print_message(const char *message, const char *detail);
// * library
void	*ft_memset(void *b, int c, size_t len);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
int	ft_strcmp(const char *str1, const char *str2);
size_t	ft_strlen(const char *s);
char	*ft_strrchr(const char *s, int c);
char	*ft_substr(char *s, unsigned int start, size_t len);
char	*ft_strdup(char *s1);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	arr_len(char **arr);
int	ft_atoi(const char *s);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strchr(const char *s, int c);
int	ft_isdigit(int c);
bool	ft_isspace(int c);
// * split
char	**ft_split(char *s, char c);
// * get_next_line
char	*get_next_line(int fd);
// * memory utils
void free_params(t_params *params);
void free_strings(char **strings);
// * list utils
t_map *ft_createlst(char *line);
void ft_addlst(t_map **head, t_map *node);
int ft_sizelst(t_map *head);
void ft_cleanlst(t_map **head);

#endif