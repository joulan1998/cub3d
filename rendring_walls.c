#include  "includes/cub3d.h"


void render_wall(t_root *root, t_ray *ray, int stripID)
{
    float distanceProjWall = (root->win_w / 2) / tan(FOV / 2);
    float projectedWallHeight = (TILE_SIZE / ray->distance) * distanceProjWall;
    int wallStripeHeight = (int)projectedWallHeight;

    int wallTopPixel = (root->win_h / 2) - (wallStripeHeight / 2);
    if (wallTopPixel < 0)
        wallTopPixel = 0;

    int wallBottomPixel = (root->win_h / 2) + (wallStripeHeight / 2);
    if (wallBottomPixel > root->win_h)
        wallBottomPixel = root->win_h;

    // Draw vertical line for the strip
    for (int y = wallTopPixel; y < wallBottomPixel; y++)
    {
        my_mlx_pixel_put(&root->mlx_img, stripID, y, RED);  // Use stripID for x-coordinate
    }
}

// void render_wall(t_root *root, t_ray *ray, int strip_id)
// {
//     float distanceProjWall = (root->win_w / 2) / tan(FOV / 2);
//     float projectedWallHeight = (TILE_SIZE / ray->distance) * distanceProjWall;
//     int wallStripeHeight = (int)projectedWallHeight;

//     int wallTopPixel = (root->win_h / 2) - (wallStripeHeight / 2);
//     if (wallTopPixel < 0)
//         wallTopPixel = 0;

//     int wallBottomPixel = (root->win_h / 2) + (wallStripeHeight / 2);
//     if (wallBottomPixel > root->win_h)
//         wallBottomPixel = root->win_h;

//     // ** Render Ceiling (optional) **
//     for (int y = 0; y < wallTopPixel; y++)
//     {
//         my_mlx_pixel_put(&root->mlx_img, strip_id, y, WHITE); // Use a ceiling color
//     }

//     // ** Render Wall **
//     for (int y = wallTopPixel; y < wallBottomPixel; y++)
//     {
//         my_mlx_pixel_put(&root->mlx_img, strip_id, y, BLACK); // Change color based on texture
//     }

//     // ** Render Floor (optional) **
//     for (int y = wallBottomPixel; y < root->win_h; y++)
//     {
//         my_mlx_pixel_put(&root->mlx_img, strip_id, y, WHITE); // Use a floor color
//     }
// }


// void render_wall(t_root * root, t_ray *ray)
// {
//     int i = 0;
//     float distanceProjWall;
//     float projectedWallheight;
//     float wallStripeHeight;
//     float wallTopPixel;
//     float wallButtomixel;

//     // while (i < NUM_RAYS)
//     // {
//         distanceProjWall = (root->win_w / 2) / tan(FOV / 2);
//         projectedWallheight = (TILE_SIZE / ray->distance) * distanceProjWall;
//         wallStripeHeight = (int) projectedWallheight;
//         wallTopPixel = (root->win_h / 2) - (wallStripeHeight / 2);
//         if (wallTopPixel < 0)
//             wallTopPixel = 0;
//         wallButtomixel = (root->win_h / 2) + (wallStripeHeight / 2);
//         if (wallButtomixel < root->win_h)
//             wallTopPixel = root->win_h;
//         int y = wallTopPixel;
//         while (y < wallButtomixel)
//         {
//             my_mlx_pixel_put(&root->mlx_img,(int)y,(int)0,RED);
//             y++;
//         }
        
        
//         // i++;
//     // }

// }