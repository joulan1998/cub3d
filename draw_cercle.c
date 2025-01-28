#include "includes/cub3d.h"

void draw_circle(t_root *root, int center_y, int center_x, int color, int radius)
{
    int x, y;

    for (y = center_y - radius; y <= center_y + radius; y++)
    {
        for (x = center_x - radius; x <= center_x + radius; x++)
        {
            if (((x - center_x) * (x - center_x) + (y - center_y) * (y - center_y)) <= (radius * radius))
            {
                my_mlx_pixel_put(&root->mlx_img, x, y, color);
            }
        }
    }
}
