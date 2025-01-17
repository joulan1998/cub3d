#include "../includes/cub3d.h"


void    dda(t_ray   **ray)
{

    // int side;
     int i = 0;
    // ray = local;
    while ((*ray)->hit == 0)
    {
        //jump to next map square, either in x-direction, or in y-direction
        if ((*ray)->sideDistX < (*ray)->sideDisty)
        {
          (*ray)->sideDistX += (*ray)->sideDistX;
          (*ray)->mapX += (*ray)->stepX;
          (*ray)->side = 0;
        }
        else
        {
            (*ray)->sideDisty += (*ray)->deltaDistY;
            (*ray)->mapY += (*ray)->stepY;
            (*ray)->side = 1;
        }
           //Check if ray has hit a wall
        // printf(" the resut of ray->mapX id %d\n",(*ray)->mapX);
        // printf(" the resut of ray->mapy id %d\n",(*ray)->mapY);
        // printf(" the resut of I id %d\n",i);
        // printf(" the resut of I id %s\n",(*ray)->map[1]);
        i++;
        // exit(32);
        if ((*ray)->map[(*ray)->mapY][(*ray)->mapX] > FLOOR) (*ray)->hit = 1;
    } 
    // if ((*ray)->side == 1)
    if ((*ray)->side == 0)
        (*ray)->perpWallDist = ((*ray)->sideDistX - (*ray)->deltaDistX);
    else
        (*ray)->perpWallDist = ((*ray)->sideDisty - (*ray)->deltaDistY);
    printf(" the final resut of ray->mapy id %d\n",(*ray)->mapY);
    printf(" the final resut of ray->mapx id %d\n",(*ray)->mapX);
    printf(" the SIDE = %d\n",(*ray)->side);
    printf(" the HIT = %d\n",(*ray)->hit);
    printf(" the final resut of I id %d\n",i);
    printf(" rhe distance to the WALL ==>>>> [%f]\n",(*ray)->perpWallDist);

}

t_line *set_line(t_ray **ray)
{

    t_line  *local;
    double wall_x;
    local = (t_line *)malloc(sizeof(t_line *));
    if ((*ray)->side == 1)
	    wall_x = (*ray)->mapY + (*ray)->perpWallDist * (*ray)->RayDiry;
    else
	    wall_x = (*ray)->mapX + (*ray)->perpWallDist * (*ray)->RayDirx;
    wall_x -= floor(wall_x); //make it start from 0
    local->x =  wall_x;
    return (local);
}

void    ray_casting(void *mlx, void *win, char **map, t_player *player)
{
    t_ray *ray;
    t_line  *line;
    ray = malloc(sizeof(t_ray * ));
    double dirx = 0;
    double diry = 1;
    double planex = 0;
    double planey = 0.66;
    double camerax = 0.02;
    double r = 0.02;
    // double r = 0.87;
    // int posX =1;
    // int posY =4;
    int posX = player->player_x;
    int posY = player->player_y;
    printf("the HORIZONTAL direction is %f\n",dirx);
    printf("the VERTICAL direction is %f\n",diry);
    printf("the posY is %d\n",posY);
    printf("the posX is %d\n",posX);
    printf("****************************************************************\n");
    
    ray->map = map;
    ray->hit = 0;
    ray->mapX = (int)posX;
    ray->mapY = (int)posY;
    ray->mlx = mlx;
    ray->win = win;
    ray->RayDirx = dirx +planex *camerax;
    ray->RayDiry = diry +planey *camerax;
    if (ray->RayDirx == 0)
        ray->deltaDistX = 1e30;
    else
        ray->deltaDistX = fabs(1/ray->RayDirx);
    if (ray->RayDiry == 0)
        ray->deltaDistY = 1e30;
    else
        ray->deltaDistY = fabs(1/ray->RayDiry);
    if (ray->RayDirx< 0)
    {
      ray->stepX = -1;
      ray->sideDistX = (posX - ray->mapX) * ray->deltaDistX;
    }
    else
    {
      ray->stepX = 1;
      ray->sideDistX = (ray->mapX + 1.0 - posX) * ray->deltaDistX;
    }
    if (ray->RayDiry < 0)
    {
      ray->stepY = -1;
      ray->sideDisty = (posY - ray->mapY) * ray->deltaDistY;
    }
    else
    {
      ray->stepY = 1;
      ray->sideDisty = (ray->mapY + 1.0 - posY) * ray->deltaDistY;
    }
    
    dda(&ray);
    line = set_line(&ray);
    printf("THE VALUE OF THE LINR->X is %f\n",line->x);
    // exit(8);

}
