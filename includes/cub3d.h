#ifndef CUB3D_H
#define CUB3D_H

#include <libc.h>
#include "../MLX/mlx.h"

// #include <mlx.h>
#include <math.h>
#include <stdbool.h>
typedef struct s_cub t_cub;
// #define PALEYR_X    
#define WALL        '1'
#define FLOOR        '0'
#define ONE         '1'
#define ZERO        '0'
#define PLAYER      'N'
#define FOV         (60 * (M_PI / 180))
#define WALL_STRIPE  1
#define NUM_RAYS    (MAP_WITH*TILE_SIZE) / WALL_STRIPE
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
    float rayAngle;
    int wallHitX;
    int wallHitY;
    int distance;
    int facingDown;
    int facingUp;
    int facingRight;
    int facingLeft;

    
    // t_ray   *next;
} t_ray;
typedef struct s_player
{
    void *mlx;
    void *win;
    char **map;
    int MapX ;
    int MapY ;
    float rotationAngle;
    int player_y;
    int player_x;
    int turnDir;
    int walkDir;
    int turnSpeed;
    int walkSpeed;

} t_player;

typedef struct s_root
{
    void *mlx;
    void *win;
    char **map;
    int map_h;
    int win_w;
    int win_h;
    int map_w;
    t_player *player;
} t_root;
// ***********************************************************************

void    parsing(t_root *root);
void initialize_data(t_root *root,char ***map,t_player **player);
char **reading_map(int fd);
int move_player(int keycode, t_root *root);
int **map_handling(int map[MAP_HEIGHT][MAP_WIDTH]);
void draw_squar(t_root * root, int y ,int x,int color,int size, int exist);
void draw_circle(t_root *root, int center_x, int center_y, int color, int radius);
void draw_ray_up(t_root *root, int y ,int x,int color, char **map);
void    ray_casting(void *mlx, void *win, char **map,t_player *player);
void draw_line(t_root *root, int start_y , int start_x, int  end_y ,int end_x, int color);
void cast_allRays(t_player *player);
// ***********************************************************************

int count_lines(char **map);

#endif