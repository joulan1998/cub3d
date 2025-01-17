#ifndef CUB3D_H
#define CUB3D_H

#include <libc.h>
// #include "../minilibx-linux/mlx.h"
#include <mlx.h>
#include <math.h>
typedef struct s_cub t_cub;
// #define PALEYR_X    
#define WALL        '1'
#define FLOOR        '0'
#define ONE         '1'
#define ZERO        '0'
#define PLAYER      'N'
#define MAP_WIDTH   9
#define MAP_HEIGHT  7
#define TILE_SIZE  40
// #define HALF_TILE_SIZE  20
#define HALF_TILE_SIZE  TILE_SIZE/2
#define RED         0xff0000
#define GREEN       0x00FF00
#define BLUE        0x0000FF
#define BLACK       0x000000
#define PURPLE       0xffffff
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

typedef  struct  s_line
{
	float  x; //the x coordinate of line relative to screen
	int  y; //the current pixel index of the line (along y axis)
	int  y0; //y start index of drawing texture
	int  y1; //y end index of drawing texture
	int  tex_x; //x coordinate of texture to draw
	int  tex_y; //y coordinate of texture to draw
} t_line;

typedef struct s_ray
{
    int index;
    void *mlx;
    void *win;
    char **map;
    int stepX;
    int stepY;
    int mapX;
    int mapY;
    // int mapp[MAP_HEIGHT][MAP_WIDTH];
    // int (*map)[MAP_HEIGHT][MAP_WIDTH];
    int player_y;
    int player_x;
    double sideDistX;
    double RayDirx;
    double RayDiry;
    double deltaDistX;
    double deltaDistY;
    double sideDisty;
    int hit ;
    int side ; // could be EAST or WEST depenfding if it 0 or 1
    double perpWallDist;
    
    // t_ray   *next;
} t_ray;
typedef struct s_player
{
    void *mlx;
    void *win;
    char **map;
    int MapX ;
    int MapY ;
    // int mapp[MAP_HEIGHT][MAP_WIDTH];
    // int (*map)[MAP_HEIGHT][MAP_WIDTH];
    int player_y;
    int player_x;
    t_cub *data;
} t_player;

typedef struct s_cub
{
    void *mlx;
    void *win;
    char **map;
    int map_height;
    int map_width;
    t_player *player;
} t_cub;
// ***********************************************************************

int move_player(int keycode, t_player *player);
int **map_handling(int map[MAP_HEIGHT][MAP_WIDTH]);
void draw_squar(void *mlx , void *win, int y ,int x,int color,int size, int exist);
void draw_ray_up(void *mlx , void *win, int y ,int x,int color, char **map);
void    ray_casting(void *mlx, void *win, char **map,t_player *player);
// ***********************************************************************

int count_lines(char **map);

#endif