/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-garr <ael-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 14:43:56 by ael-garr          #+#    #+#             */
/*   Updated: 2025/03/13 17:33:19 by ael-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <libc.h>
// # include "../MLX/mlx.h"
# include <mlx.h>
# include <math.h>
# include <stdbool.h>

typedef struct s_cub	t_cub;
# define WALL '1'
# define FLOOR '0'
# define ONE '1'
# define ZERO '0'
# define PLAYER 'N'
# define FOV (60 * (M_PI / 180))
# define WALL_STRIPE  1
# define SCALE  0.3
# define TILE_SIZE  40
# define MAP_WIDTH   15
# define MAP_HEIGHT  7
# define NUM_RAYS    (MAP_WIDTH*TILE_SIZE) / WALL_STRIPE
# define WIN_MLX_W  1920
# define WIN_MLX_H  1080
# define HALF_TILE_SIZE  TILE_SIZE/2
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
	bool f_u;
	bool f_d;
	bool f_r;
	bool f_l;
}	t_compass;

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
	t_player	*player;
	t_ray		*ray;
}	t_root;

char	**ft_split(char const *s, char c);
void	ft_putstr_fd(char *s, int fd);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
char	*ft_strchr(const char *chain, int c);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
char	*ft_strjoin(char const *s1, char const *s2);
int		is_number(char *str);
int		ft_atoi(const char *str);
void	parsing(t_root *root);
void	initialize_data(t_root *root, char ***map, t_player *player);
char	**reading_map(int fd);
int		move_player(int keycode, t_root *root);
int		**map_handling(int map[MAP_HEIGHT][MAP_WIDTH]);
void	draw_squar(t_root *root, int y, int x, int color);
void	draw_circle(t_root *root, t_pos *cnt_cor, int color, int radius);
void	draw_ray_up(t_root *root, int y, int x, int color, char **map);
void	ray_casting(void *mlx, void *win, char **map, t_player *player);
void	draw_line(t_root *root, int start_y, int start_x, int end_y, int end_x, int color);
void	render_player(t_root *root);
void	my_mlx_pixel_put(t_mlx *data, int x, int y, int color);
void	update(t_root **root);
void	render_map(t_root *root);
void	render_dir(t_root *root);
int		maphaswallat(t_root *root, float y, float x);
void	castallrays(t_root *root);
t_ray	*create_ray(float rayangle);
void	cast_allrays(t_root *root);
// t_ray *cast_ray(t_root *root,t_ray *ray,float rayangle, int i);
t_ray	*cast_ray(t_root *root, t_ray *ray, float rayangle);
float	normalizeangle(float angle);
void	render_wall(t_root *root, t_ray *ray, int strip_id, float anglee);
void	mini_map(t_root **root);
int		count_lines(char **map);
// t_pos	*cal_v_d(t_root *root, float angl, bool facingdwn, bool facingup, bool facingright, bool facingleft);
t_pos	*cal_v_d(t_root *root, float angl, t_compass *cmps);
// void	cal_intcep(float *x, float *y, float p_x, float p_y, float angle, bool ver, bool f_r, bool f_d);
void	cal_intcep(float *x, float *y, float p_x, float p_y, float angle, bool ver, t_compass *cmps);
t_pos	*create_pos(float x, float y);
float	normalizeangle(float angle);
int		distance_to_wall(float x1, float y1, float x2, float y2);
void	render_dir_mini(t_root *root);
void	sqr_mini(t_root *root, int y, int x, int color);
t_compass *create_compass(bool f_u, bool f_d, bool f_r, bool f_l);

#endif