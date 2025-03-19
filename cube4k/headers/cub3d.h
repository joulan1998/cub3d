#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>      
# include <unistd.h>  
# include <math.h> 
# include <stdbool.h>
# include <fcntl.h>

# define VALID_MAP_CHARS "01NSEW \n"
# define MAP_CONTENT_CHARS "01NSEW " // todo: add all the possible spaces here
# define VALID_PLAYER_POSITION "NSEW"
# define INVALID_NBR_ARGS "Error\n Invalid number of arguments"
# define MALLOC_ERROR "Memory allocation failed"
# define INVALID_PATH "Error\n Invalid path"
# define INVALID_FILE_EXTENSION "Error\n Invalid file extension"
# define PARSING_ERROR "Error\n==> Parsing failed"
# define OPEN_ERROR "Error\n Could not open file"
# define SPLIT_FAILED ": Split failed"
# define MISSING_PARAMS ": Missing parameters"
# define RGB_ERROR ": Invalid RGB values"
# define INVALID_CHARACTER ": Invalid character in map"
# define INVALID_MAP "Invalid map"
# define INVALID_PLAYER "Invalid player"
# define MULTIPLE_PLAYERS "Multiple players found"
# define INVALID_MAP_BORDERS "Invalid map borders"
# define INVALID_MAP_CONTENT "Invalid map content"
# define INVALID_TEXTURES "Invalid textures"
# define MAP_ORDER_ERROR "Parameters are missing or the map elements aren't in order"
# define UNKOWN_OBJECT "Unknown object"
# define FOUND_DUPLICATE "Found duplicate"
# define INVALID_TEXTURE_EXT "Invalid texture extension"
# define INVALID_TEXTURE_FILE "Cannot open texture file"
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
	bool found_unkown;
	bool found_duplicate;
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
bool is_valid_file_extension( char *file_path,  char *extension);
bool is_valid_path( char *path);
// * printing utils
void    print_message( char *message,  char *detail);
// * library
void	*ft_memset(void *b, int c, size_t len);
int	ft_strncmp( char *s1,  char *s2, size_t n);
int	ft_strcmp( char *str1,  char *str2);
size_t	ft_strlen( char *s);
char	*ft_strrchr( char *s, int c);
char	*ft_substr(char *s, unsigned int start, size_t len);
char	*ft_strdup(char *s1);
char	*ft_strjoin(char  *s1, char  *s2);
size_t	arr_len(char **arr);
int	ft_atoi( char *s);
char	*ft_strtrim(char  *s1, char  *set);
char	*strtrim_texture(char  *s1, char  *set);
char	*ft_strchr( char *s, int c);
size_t	ft_strlcpy(char *dst,  char *src, size_t dstsize);
int	ft_isdigit(int c);
bool	ft_isspace(int c);
char **split_two( char *line);
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
bool	found_player_position(char *map_line);
bool	validate_map_content(t_params *params);
bool	parse_texture_line(int i, t_params *params,
	t_tracker *tracker, char **splited_line);
bool	parse_color_param(t_params *params, t_tracker *tracker,
	char **splited_line, bool is_floor);
bool	validate_textures(t_params *params);
bool	is_map_line(char *line);
bool	is_valid_map(t_params *params);

#endif