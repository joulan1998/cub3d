#include "../includes/cub3d.h"
int normalizeAngle(float angle)
{
    int res;
    res = fmod(angle,(M_PI * 2));
    printf("the vlue if anggle is %f\n",angle);
    printf("the vlue if angle after is %d\n",res);
    if (res < 0)
        res = (2 * M_PI) + res;
    printf("the vlue if angle after is >>>>>>%d\n",res);
    // exit(10);
    return (res);
}
t_ray *create_ray(float rayAngle)
{
    t_ray *res;

    res = malloc(sizeof(t_ray * ) * 1);

    res->rayAngle= normalizeAngle(rayAngle);
    res->distance=0;
    res->wallHitX=0;
    res->facingDown = (rayAngle >0 && rayAngle < M_PI);
    res->facingUp = !res->facingDown;
    res->facingRight = (rayAngle > (0.5 * M_PI) || rayAngle > (1.5 * M_PI));
    res->facingLeft = !res->facingRight;
    printf("the niramalzed value is %f\n",res->rayAngle);
    // exit(9);
    return(res);
}


void cast(int columnid , t_player *player,t_ray *ray)
{
    int yintesept;
    int xintesept;
    int xstep;
    int ystep;
    int nextHtouchX;
    int nextHtouchY;
    int foundHWallHit = false;
    int wallhitX = 0;
    int wallhitY = 0;

    yintesept = floor(player->player_y);
    if (ray->facingDown)
        yintesept += TILE_SIZE;
    else 
        yintesept += 0;

    // printf("**the player_x is %d\n",player->player_x);
    // printf("**the player_y is %d\n",player->player_y);
    // printf("**the ray_angle is %d\n",ray->rayAngle);
    printf("**********************************\n");
    xintesept = player->player_x + (yintesept - player->player_y) / tan(ray->rayAngle);
    ystep = TILE_SIZE;
    if (ray->facingUp)
        ystep *= -1;
    else 
        ystep *= 1;
    xstep = TILE_SIZE / tan(ray->rayAngle);
    if (ray->facingLeft && xstep > 0)
        xstep *= -1;
    else 
        xstep *= 1;
    if (ray->facingRight && xstep < 0)
        xstep *= -1;
    else 
        xstep *= 1;
    nextHtouchX = xintesept;
    nextHtouchY = yintesept;
    if (ray->facingUp)
        nextHtouchY--;
    // while(!foundHWallHit)
    while (nextHtouchX >= 0 && nextHtouchX <= (MAP_HEIGHT*40) && nextHtouchY >= 0 && nextHtouchY <= (MAP_HEIGHT*40))
    {
        // printf("**the Xintecept is %d\n",xintesept);
        // printf("**the x of the wall is %d<<<<<<<\n",nextHtouchX);
        // printf("**the y of the wall is %d<<<<<<<\n",nextHtouchY);
        // printf("** xstep =  %d\n",xstep);
        // printf("** ystep =  %d\n",ystep);i
        // if (player->map[nextHtouchY/40][nextHtouchX/40] > FLOOR)
        // {
        //     foundHWallHit = true;
        //     wallhitX = nextHtouchX;
        //     wallhitY = nextHtouchY;
        //     printf("the xstep is %d\n",xstep);
        //     printf("the y0step is %d\n",ystep);
        //     // draw_line(player->mlx, player->win,player->player_y*40,player->player_y*40,wallhitY *40,wallhitX*40,RED);
        //     puts("before");
        //     // draw_line(player->mlx, player->win,player->player_y*40,player->player_y*40,0,0,RED);
        //     return;
        //     puts("after");
        // printf("$$$$$$$$$$$$$$$$$$$$$$$$$$%d\n",foundHWallHit);
        //     // exit(17);
        //     break;
        // }
        // else
        // {
        //     nextHtouchX += xstep;
        //     nextHtouchY += ystep;
        // }
        // exit(66);
    }
}
// void draw_line(t_data *data, t_vector start, t_vector end, int color)
void draw_line(t_root *root, int start_y , int start_x, int  end_y ,int end_x, int color)
{
    // printf("x_start =%d\n",start_x);
    // printf("y_start =%d\n",start_y);
    // printf("x_end =%d\n",end_x);
    // printf("y_end =%d\n",end_y);
    int i;
    double x = end_x - start_x;
    double y = end_y - start_y;
    double length = sqrt(x * x + y * y);
    double addx = x / length;
    double addy = y / length;
    x = start_x;
    y = start_y;

    for (i = 0; i < length; i += 1) {
        mlx_pixel_put(root->mlx,root->win,(int)round(x), (int)round(y),color );
        x += addx;
        y += addy;
    }
}
// void render(int x, int y,t_player *player)
// {
//     stroke
// }
// void draw()
// {
//     for(all ray of rays)
//         ray.render;
// }


// void cast_all_rays(t_player *player)
// {
//     int columnid = 0;
//     int ray_angle = player->rotationAngle - (FOV / 2);

//     t_ray *rays;
//     int i =0;
//     while (i < NUM_RAYS)
//     {
//         var ray = new ray(rayAngle);
//         rays.push(ray);
//         ray_angle += FOV / NUM_RAYS;
//         columnid++;
//     }
    


// }

void cast_allRays(t_player *player)
{
    int i =0;
    int columnid = 0;
    float     ray_angle = player->rotationAngle - (FOV / 2);
    // exit(28);
    // while (i < (60/(7*40)))
    while (i < 1)
    {
        printf("&&&&&&&&&&the ray angle is %f\n",ray_angle);
        // exit(9);
        // t_ray *ray =  create_ray(8.554545);
        t_ray *ray =  create_ray(ray_angle);
        cast(columnid,player,ray);
        ray_angle += FOV/(60/40);
        columnid++;
        printf("&&&&&&&&&&the ray angle is %f\n",ray_angle);
        // exit(78);
    }
    
}
// }
// void cast_allRays(t_player *player)
// {
//     int i =0;
//     int columnid = 0;
//     int     ray_angle = player->rotationAngle - (FOV / 2);
//     while (i < (60/(7*40)))
//     {
//         var ray = new ray(ray_angle);
//         ray.cast(columnid);
//         ray_angle += FOV/(60/40);
//         columnid++;
//     }
    
// }