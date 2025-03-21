/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-garr <ael-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 14:43:56 by ael-garr          #+#    #+#             */
/*   Updated: 2025/03/21 14:35:00 by ael-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <libc.h>
# include <mlx.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>      
# include <unistd.h>  
# include <fcntl.h>
# define VALID_MAP_CHARS "01NSEW \n"
# define MAP_CONTENT_CHARS "01NSEW "
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
# define MAP_ORDER_ERROR "Params are missing or the map elements isn't in order"
# define UNKOWN_OBJECT "Unknown object"
# define FOUND_DUPLICATE "Found duplicate"
# define INVALID_TEXTURE_EXT "Invalid texture extension"
# define INVALID_TEXTURE_FILE "Cannot open texture file"

typedef struct s_tracker
{
	bool	no_tracker;
	bool	so_tracker;
	bool	we_tracker;
	bool	ea_tracker;
	bool	floor_tracker;
	bool	ceiling_tracker;
	bool	found_the_map;
	bool	found_the_player;
	bool	found_empty_line;
	bool	found_unkown;
	bool	found_duplicate;
}	t_tracker;

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
}	t_params;

typedef struct s_map
{
	char			*line;
	struct s_map	*next;
}	t_map;

// * 00 initialization functions
void		init_params(t_params *params);

// * 01 parsing functions
bool		check_if_empty_line(char *line);
bool		check_if_valid(t_tracker *tracker, char *line);
int			parse_color(char **splited_line);
bool		parse_map_line(char *line, t_map **map,
				t_tracker *tmp, t_params *params);
bool		parse_file_line(char *line, t_tracker *tmp, t_params *params);
bool		extract_cleaned_map(t_params *params, t_map **map);
bool		parser(t_params *params, char *map_file);

// * 06 utils functions
// * file utils
bool		is_valid_file_extension(char *file_path, char *extension);
bool		is_valid_path( char *path);
// * printing utils
void		print_message(char *message, char *detail);
// * library
void		*ft_memset1(void *b, int c, size_t len);
int			ft_strncmp1(char *s1, char *s2, size_t n);
int			ft_strcmp1(char *str1, char *str2);
size_t		ft_strlen1(char *s);
char		*ft_strrchr1(char *s, int c);
char		*ft_substr1(char *s, unsigned int start, size_t len);
char		*ft_strdup1(char *s1);
char		*ft_strjoin1(char *s1, char *s2);
size_t		arr_len1(char **arr);
int			ft_atoi1(char *s);
char		*ft_strtrim1(char *s1, char *set);
char		*strtrim_texture(char *s1, char *set);
char		*ft_strchr1(char *s, int c);
size_t		ft_strlcpy1(char *dst, char *src, size_t dstsize);
int			ft_isdigit1(int c);
bool		ft_isspace1(int c);
char		**split_two(char *line);
// * split
char		**ft_split(char *s, char c);
// * get_next_line
char		*get_next_line(int fd);
// * memory utils
void		free_params(t_params *params);
void		free_strings(char **strings);
// * list utils
t_map		*ft_createlst(char *line);
void		ft_addlst(t_map **head, t_map *node);
int			ft_sizelst(t_map *head);
void		ft_cleanlst(t_map **head);
bool		found_player_position(char *map_line);
bool		validate_map_content(t_params *params);
bool		parse_texture_line(int i, t_params *params,
				t_tracker *tracker, char **splited_line);
bool		parse_color_param(t_params *params, t_tracker *tracker,
				char **splited_line, bool is_floor);
bool		validate_textures(t_params *params);
bool		is_map_line(char *line);
bool		is_valid_map(t_params *params);
# define WALL '1'
# define FLOOR '0'
# define ONE '1'
# define ZERO '0'
# define PLAYER 'N'
# define WALL_STRIPE  1
# define SCALE  0.3
# define TILE_SIZE  40
# define MAP_WIDTH   33
# define MAP_HEIGHT  7
# define WIN_MLX_W  1920
# define WIN_MLX_H  1080
# define RED         0xff0000
# define GREEN       0x00ff00
# define BLUE        0x0000ff
# define BLACK       0x000000
# define WHITE       0xffffff
# define PURPLE      0xffffff
# define YELLOW      0xffff00

typedef struct s_pos
{
	float	x_pos;
	float	y_pos;
}	t_pos;

typedef struct s_ray
{
	float	rayangle;
	float	wallhitx;
	float	wallhity;
	float	distance;
	int		wallhitvertical;
	int		facingup;
	int		facingdwn;
	int		facingright;
	int		facingleft;
	int		wallhircontent;
}	t_ray;

typedef struct s_rndr_str
{
	float	perp_dist;
	float	distanceprojwall;
	float	projwallheight;
	int		wallstripeheight;
	int		wallbottompixel;
	int		walltoppixel;
	float	wall_x;
	int		y;
}	t_rndr_str;

typedef struct s_player
{
	void	*mlx;
	void	*win;
	char	**map;
	int		mapx;
	int		mapy;
	float	rot_angl;
	int		*player_y;
	int		*player_x;
	int		turndir;
	int		walkdir;
	int		turnspeed;
	int		walkspeed;
}	t_player;

typedef struct s_compass
{
	bool	f_u;
	bool	f_d;
	bool	f_r;
	bool	f_l;
}	t_compass;

typedef struct s_i_infos
{
	float	p_x;
	float	p_y;
	float	angl;
	bool	ver;
}	t_i_infos;

typedef struct s_mlx
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_mlx;

typedef struct s_root
{
	void		*mlx;
	void		*win;
	t_mlx		mlx_img;
	char		**map;
	int			map_h;
	int			win_w;
	int			win_h;
	int			map_w;
	int			floor_color;
	int			ceiling_color;
	t_player	*player;
	t_ray		*ray;
	t_mlx		left_wall_texture;
	t_mlx		right_wall_texture;
	t_mlx		front_wall_texture;
	t_mlx		back_wall_texture;
	int			tex_width;
	int			tex_height;
	t_mlx		tst;
}	t_root;

void		ft_putstr_fd(char *s, int fd);
size_t		ft_strlen(const char *s);
char		*ft_strdup(const char *s1);
char		*ft_strchr(const char *chain, int c);
int			ft_isalpha(int c);
int			ft_isdigit(int c);
char		*ft_strjoin(char const *s1, char const *s2);
int			is_number(char *str);
int			ft_atoi(const char *str);
void		parsing(t_root *root);
void		initialize_data(t_root *root, t_params *params, t_player *player);
char		**reading_map(int fd);
int			move_player(int keycode, t_root *root);
int			**map_handling(int map[MAP_HEIGHT][MAP_WIDTH]);
void		draw_squar(t_root *root, int y, int x, int color);
void		draw_circle(t_root *root, t_pos *cnt_cor, int color, int radius);
void		ray_casting(void *mlx, void *win, char **map, t_player *player);
void		draw_line(t_root *root, int end_y, int end_x, int color);
void		render_player(t_root *root);
void		my_mlx_pixel_put(t_mlx *data, int x, int y, int color);
void		update(t_root **root);
void		render_map(t_root *root);
void		render_dir(t_root *root);
int			maphaswallat(t_root *root, float y, float x);
void		castallrays(t_root *root);
t_ray		*create_ray(float rayangle);
void		cast_allrays(t_root *root, int rays_nbr);
t_ray		*cast_ray(t_root *root, t_ray *ray, float rayangle);
float		normalizeangle(float angle);
void		render_wall(t_root *root, t_ray *ray, int strip_id, float anglee);
void		mini_map(t_root **root);
int			count_lines(char **map);
t_pos		*cal_v_d(t_root *root, float angl, t_compass *cmps);
void		cal_intcep(float *x, float *y, t_i_infos *inf, t_compass *cmps);
t_pos		*create_pos(float x, float y);
float		normalizeangle(float angle);
int			distance_to_wall(float x1, float y1, float x2, float y2);
void		render_dir_mini(t_root *root);
void		sqr_mini(t_root *root, int y, int x, int color);
t_compass	*create_compass(bool f_u, bool f_d, bool f_r, bool f_l);
t_i_infos	*create_info(t_root *root, float ang, bool ver);
int			get_texture_pixel(t_mlx *texture, int tex_x, int tex_y);
int			load_xpm_texture(void *mlx, char *texture_path, t_mlx *texture);
t_pos		*return_pos_h(t_root *root, t_compass *cmps, t_pos *dist, float s);
t_pos		*return_pos_v(t_root *root, t_compass *cmps, t_pos *dist, float s);

#endif