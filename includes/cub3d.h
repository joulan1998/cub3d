#ifndef CUB3D_H
#define CUB3D_H

#include <libc.h>
// #include "../minilibx-linux/mlx.h"
#include <mlx.h>
#define ONE         1
#define ZERO        0
#define MAP_WIDTH   9
#define MAP_HEIGHT  7
#define TILE_SIZE  40
#define RED         0xff0000
#define GREEN       0x00FF00
#define BLUE        0x0000FF
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


// typedef struct s_cub
// {
//     void *mlx;
//     void *win;
//     int win_height;
//     int win_height;
//     int map_height;
//     int map_width;
// } t_cub;

int count_lines(char **map);

#endif