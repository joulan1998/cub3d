#include  "includes/cub3d.h"



void render_wall(t_root *root, t_ray *ray, int strip_id, float anglee)
{
    float perp_dist = ray->distance  * cos((double)(anglee - root->player->rotationAngle));
    float distanceProjWall = (root->win_w / 2) / tan(FOV / 2);
    float projectedWallHeight = (TILE_SIZE / perp_dist) * distanceProjWall;
    int wallStripeHeight = (int)projectedWallHeight;
    int wallBottomPixel;
    int wallTopPixel;
    int y;

    wallTopPixel = (root->win_h / 2) - (wallStripeHeight / 2);
    wallBottomPixel = (root->win_h / 2) + (wallStripeHeight / 2);
    if (wallTopPixel < 0)
        wallTopPixel = 0;
    if (wallBottomPixel > root->win_h)
        wallBottomPixel = root->win_h;
    y = 1;
    while (y < wallTopPixel)
    {   
        my_mlx_pixel_put(&root->mlx_img, strip_id, y, BLUE);
        y++;
    }
    y = wallTopPixel;
    while (y <  wallBottomPixel)
    {
        // if ((!(y %10) && !(y%40)) || (!(strip_id % 10) && !(strip_id % 40)))
        if (!(strip_id % 10) && !(strip_id % 40))
            my_mlx_pixel_put(&root->mlx_img, strip_id, y, RED);
        else
            my_mlx_pixel_put(&root->mlx_img, strip_id, y, WHITE);
        y++;
    }
    y = wallBottomPixel;
    while (y < root->win_h)
    {
        my_mlx_pixel_put(&root->mlx_img, strip_id, y++, GREEN);
    }
}
