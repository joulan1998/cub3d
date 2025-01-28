#include "includes/cub3d.h"

int distane_to_wall(int x1, int y1, int x2, int y2)
{
    return(sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

float normalizeAngle(float angle)
{
    float res;
    res = fmod(angle,(M_PI * 2));
    if (res < 0)
        res = (2 * M_PI) + res;
    return (res);
}
void cast_ray(t_root *root,t_ray *ray,int rayangle, int stripid)
{
    float yintesept;
    float xintesept;
    float xstep;
    float ystep;
    float nextHtouchX;
    float nextHtouchY;
    float nextVtouchX; //**
    float nextVtouchY; //**
    int foundHWallHit = false;
    int foundVWallHit = false; //**
    float wallHORhitX = 0;
    int wallVERhitX = 0; //**
    float wallHORhitY = 0;
    int wallVERhitY = 0; //**
    int horwallcontent = 0;
    int verwallcontent = 0; //**
    float xtocheck;
    float ytocheck;
    float facingLeft;
    float facingRight;
    float facingUp;
    float facingDown;
    yintesept = floor(*root->player->player_y / TILE_SIZE) * TILE_SIZE;
    yintesept += facingDown ? TILE_SIZE : 0;

    xintesept = *root->player->player_x + (yintesept - *root->player->player_y) / tan(rayangle);
    
    ystep = TILE_SIZE ;
    if (facingUp)
        ystep *= -1 ;
    else
        ystep *= 1;
    xstep = TILE_SIZE /tan(rayangle);
    if (facingLeft && xstep > 0)
        xstep *= -1;
    else
        xstep *= 1;
    if (facingLeft && xstep < 0)
        xstep *= -1;
    else
        xstep *= 1;

    nextHtouchX = xintesept;
    nextHtouchY = yintesept;
    // while(!foundHWallHit)
    while (nextHtouchX >= 0 && nextHtouchX <= root->win_w && nextHtouchY >= 0 && nextHtouchY <= root->win_h)
    {
            xtocheck = nextHtouchX;
            ytocheck = nextHtouchY;
        if (maphaswallat(root,ytocheck,xtocheck) && ytocheck < root->win_h && xtocheck < root->win_w)
        {
            foundHWallHit = true;
            wallHORhitX = nextHtouchX;
            wallHORhitY = nextHtouchY;
            horwallcontent = root->map[(int)ytocheck / TILE_SIZE][(int)xtocheck / TILE_SIZE];
            // printf("he vules ere y=%f x= %f\n",ytocheck, xtocheck);
            // exit(9);
            foundHWallHit = true;
            break;
        }
        else
        {
            nextHtouchX += xstep;
            nextHtouchY += ystep;
        }
    }
    //////// lest begin the vertical intecection with the grids
    xintesept = floor(*root->player->player_x / TILE_SIZE) * TILE_SIZE;
    xintesept += facingRight ? TILE_SIZE : 0;

    yintesept = *root->player->player_y + (xintesept - *root->player->player_x) / tan(rayangle);
    
    xstep = TILE_SIZE ;
    if (facingLeft)
        xstep *= -1 ;
    else
        xstep *= 1;
    ystep = TILE_SIZE /tan(rayangle);
    if (facingUp && xstep > 0)
        ystep *= -1;
    else
        ystep *= 1;
    if (facingDown && xstep < 0)
        ystep *= -1;
    else
        ystep *= 1;

    nextVtouchX = xintesept;
    nextVtouchY = yintesept;
    // while(!foundHWallHit)
    while (nextVtouchX >= 0 && nextVtouchX <= root->win_w && nextVtouchY >= 0 && nextVtouchY <= root->win_h)
    {
            xtocheck = nextVtouchX;
            if (facingLeft)
                xtocheck += -1;
            else 
                xtocheck += 0;
            ytocheck = nextVtouchY;
        if (maphaswallat(root,ytocheck,xtocheck) && ytocheck < root->win_h && xtocheck < root->win_w)
        {
            foundVWallHit = true;
            wallVERhitX = nextVtouchX;
            wallVERhitY = nextVtouchY;
            verwallcontent = root->map[(int)ytocheck / TILE_SIZE][(int)xtocheck / TILE_SIZE];
            foundVWallHit = true;
            break;
        }
        else
        {
            nextVtouchX += xstep;
            nextVtouchY += ystep;
        }
    }
    float horhitdistande;
    if (distane_to_wall(*root->player->player_x, *root->player->player_y,wallHORhitX,wallHORhitY))
        horhitdistande  = distane_to_wall(*root->player->player_x, *root->player->player_y,wallHORhitX,wallHORhitY);
    else 
        horhitdistande  = INT_MAX;
    float verhitdistande;
    if (distane_to_wall(*root->player->player_x, *root->player->player_y,wallVERhitX,wallVERhitY))
        verhitdistande  = distane_to_wall(*root->player->player_x, *root->player->player_y,wallVERhitX,wallVERhitY);
    else 
        verhitdistande  = INT_MAX;
    if (verhitdistande < horhitdistande)
    {
        ray->distance = verhitdistande;
        ray->wallHitX = wallVERhitX;
        ray->wallHitY = wallVERhitY;
        ray->wallhircontent = verwallcontent;
        ray->WasHitVertical = true;
    }
    else
    {
        ray->distance = horhitdistande;
        ray->wallHitX = wallHORhitX;
        ray->wallHitY = wallHORhitY;
        ray->wallhircontent = horwallcontent;
        ray->WasHitVertical = false;
    }
    ray->facingDown = facingDown;
    ray->facingUp = facingUp;
    ray->facingRight = facingRight;
    ray->facingLeft = facingLeft;
}

void cast_allRays(t_root    *root)
{
    float rayangle = root->player->rotationAngle - (FOV / 2);
    int i = 0;
    t_ray *ray = create_ray(root->player->rotationAngle);
    while (i < 1)
    {
        cast_ray(root, ray, rayangle, i);
        rayangle += 60;
    }
    
}