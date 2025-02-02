#include "includes/cub3d.h"
void render_ray(t_root *root, t_ray *ray)
{
	draw_line(root,*root->player->player_y,*root->player->player_x, ray->wallHitY, ray->wallHitX,GREEN);
}

int distane_to_wall_temp(t_pos *pos1, t_pos *pos2)
{
	return(sqrt((pos2->x_pos - pos1->x_pos) * (pos2->x_pos - pos1->x_pos) + (pos2->y_pos - pos1->y_pos) * (pos2->y_pos - pos1->y_pos)));
}
int distance_to_wall(float x1, float y1, float x2, float y2)
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

t_pos *create_pos()
{
	t_pos *res;
	res = malloc(sizeof(t_pos));
	if (!res)
		return(0);
	return(res);

}
// t_pos *cal_h_dist(t_root *root, t_ray *ray, float rayangle)
// {
//     bool    facingDown;
//     bool    facingUp;
//     bool    facingRight;
//     bool    facingLeft;
//     float   yintercept;
//     float   xintercept;
//     float   ystep;
//     float   xstep;
//     float   nextHtouchX;
//     float   nextHtouchY;
//     bool    foundHWallHit;
//     int     horWallContent;
//     float   xtocheck;
//     float   ytocheck;
//     t_pos   *res;

//     res = create_pos();
//     facingRight = rayangle < M_PI_2 || rayangle > 3 * M_PI_2;
//     facingLeft = !facingRight;
//     facingUp = !facingDown;
//     facingDown = rayangle > 0 && rayangle < M_PI;
//     yintercept = floor(*root->player->player_y / TILE_SIZE) * TILE_SIZE;
//     if (facingDown)
//         yintercept += TILE_SIZE;
//     else
//         yintercept = 0;
//     xintercept = *root->player->player_x + (yintercept - *root->player->player_y) / tan(rayangle);
//     ystep = TILE_SIZE * (facingUp ? -1 : 1);
//     xstep = TILE_SIZE / tan(rayangle);
//     if ((facingLeft && xstep > 0) || (facingRight && xstep < 0))
//         xstep *= -1;
//     nextHtouchX = xintercept;
//     nextHtouchY = yintercept;
//     horWallContent = 0;
//     foundHWallHit = false;
//     while (nextHtouchX >= 0 && nextHtouchX < root->win_w && nextHtouchY >= 0 && nextHtouchY < root->win_h)
//     {
//         xtocheck = nextHtouchX;
//         ytocheck = nextHtouchY + (facingUp ? -1 : 0); // Adjust for grid alignment
//         if (maphaswallat(root, ytocheck, xtocheck))
//         {
//             foundHWallHit = true;
//             res->x_pos = nextHtouchX;
//             res->y_pos = nextHtouchY;
//             horWallContent = root->map[(int)(ytocheck / TILE_SIZE)][(int)(xtocheck / TILE_SIZE)];
//             break;
//         }
//         else
//         {
//             nextHtouchX += xstep;
//             nextHtouchY += ystep;
//         }
//     }
//     return(res);
// }
// t_pos    *cal_v_dist(t_root *root, t_ray *ray, float rayangle)
// {
//     float   xintercept;
//     float   yintercept;
//     float   facingRight;
//     float   facingLeft;
//     float   facingUp;
//     float   facingDown;
//     float   ystep;
//     float   xstep;
//     float   nextVtouchX;
//     float   nextVtouchY;
//     int     verWallContent;
//     bool    foundVWallHit;
//     float   xtocheck;
//     float   ytocheck;
//     t_pos   *res;

//     res = create_pos();
//     xintercept = floor(*root->player->player_x / TILE_SIZE) * TILE_SIZE;
//     xintercept += facingRight ? TILE_SIZE : 0;
//     yintercept = *root->player->player_y + (xintercept - *root->player->player_x) * tan(rayangle);
//     xstep = TILE_SIZE * (facingLeft ? -1 : 1);
//     ystep = TILE_SIZE * tan(rayangle);
//     if ((facingUp && ystep > 0) || (facingDown && ystep < 0)) ystep *= -1;
//     nextVtouchX = xintercept;
//     nextVtouchY = yintercept;
//     verWallContent = 0;
//     foundVWallHit = false;
//     while (nextVtouchX >= 0 && nextVtouchX < root->win_w && nextVtouchY >= 0 && nextVtouchY < root->win_h) {
//         xtocheck = nextVtouchX + (facingLeft ? -1 : 0); // Adjust for grid alignment
//         ytocheck = nextVtouchY;

//         if (maphaswallat(root, ytocheck, xtocheck))
//         {
//             foundVWallHit = true;
//             res->x_pos = nextVtouchX;
//             res->y_pos = nextVtouchY;
//             verWallContent = root->map[(int)(ytocheck / TILE_SIZE)][(int)(xtocheck / TILE_SIZE)];
//             break;
//         }
//         else
//         {
//             nextVtouchX += xstep;
//             nextVtouchY += ystep;
//         }
//     }
//     return(res);
// }

t_ray *cast_ray(t_root *root, t_ray *ray, float rayangle, int stripid)
{
	rayangle = normalizeAngle(rayangle);

	// Ray direction
	bool facingDown = rayangle > 0 && rayangle < M_PI;
	bool facingUp = !facingDown;
	bool facingRight = rayangle < M_PI_2 || rayangle > 3 * M_PI_2;
	bool facingLeft = !facingRight;

	// Horizontal intersections
	float yintercept = floor(*root->player->player_y / TILE_SIZE) * TILE_SIZE;
	yintercept += facingDown ? TILE_SIZE : 0;

	float xintercept = *root->player->player_x + (yintercept - *root->player->player_y) / tan(rayangle);

	float ystep = TILE_SIZE * (facingUp ? -1 : 1);
	float xstep = TILE_SIZE / tan(rayangle);
	if ((facingLeft && xstep > 0) || (facingRight && xstep < 0)) xstep *= -1;

	float nextHtouchX = xintercept;
	float nextHtouchY = yintercept;

	float horHitX = 0, horHitY = 0;
	int horWallContent = 0;
	bool foundHWallHit = false;

	while (nextHtouchX >= 0 && nextHtouchX < root->win_w && nextHtouchY >= 0 && nextHtouchY < root->win_h) {
		float xtocheck = nextHtouchX;
		float ytocheck = nextHtouchY + (facingUp ? -1 : 0); // Adjust for grid alignment

		if (maphaswallat(root, ytocheck, xtocheck))
		{
			foundHWallHit = true;
			horHitX = nextHtouchX;
			horHitY = nextHtouchY;
			horWallContent = root->map[(int)(ytocheck / TILE_SIZE)][(int)(xtocheck / TILE_SIZE)];
			break;
		}
		else
		{
			nextHtouchX += xstep;
			nextHtouchY += ystep;
		}
	}

	// Vertical intersections
	xintercept = floor(*root->player->player_x / TILE_SIZE) * TILE_SIZE;
	xintercept += facingRight ? TILE_SIZE : 0;

	yintercept = *root->player->player_y + (xintercept - *root->player->player_x) * tan(rayangle);

	xstep = TILE_SIZE * (facingLeft ? -1 : 1);
	ystep = TILE_SIZE * tan(rayangle);
	if ((facingUp && ystep > 0) || (facingDown && ystep < 0)) ystep *= -1;

	float nextVtouchX = xintercept;
	float nextVtouchY = yintercept;

	float verHitX = 0, verHitY = 0;
	int verWallContent = 0;
	bool foundVWallHit = false;

	while (nextVtouchX >= 0 && nextVtouchX < root->win_w && nextVtouchY >= 0 && nextVtouchY < root->win_h) {
		float xtocheck = nextVtouchX + (facingLeft ? -1 : 0); // Adjust for grid alignment
		float ytocheck = nextVtouchY;

		if (maphaswallat(root, ytocheck, xtocheck))
		{
			foundVWallHit = true;
			verHitX = nextVtouchX;
			verHitY = nextVtouchY;
			verWallContent = root->map[(int)(ytocheck / TILE_SIZE)][(int)(xtocheck / TILE_SIZE)];
			break;
		}
		else
		{
			nextVtouchX += xstep;
			nextVtouchY += ystep;
		}
	}
	// t_pos *pos_h = cal_h_dist(root, ray,rayangle);
	// t_pos *pos_v = cal_h_dist(root, ray,rayangle);
	float horDistance = foundHWallHit ? distance_to_wall(*root->player->player_x, *root->player->player_y, horHitX, horHitY) : INT_MAX;   //the orgin
	float verDistance = foundVWallHit ? distance_to_wall(*root->player->player_x, *root->player->player_y, verHitX, verHitY) : INT_MAX;	//the orgin
	// float horDistance = foundHWallHit ? distane_to_wall_temp(&(t_pos){*root->player->player_x, *root->player->player_y}, cal_h_dist(root, ray,rayangle)) : INT_MAX;
	// float verDistance = foundVWallHit ? distane_to_wall_temp(&(t_pos){*root->player->player_x, *root->player->player_y}, cal_v_dist(root, ray,rayangle)) : INT_MAX;
	// float verDistance = foundVWallHit ? distane_to_wall(*root->player->player_x, *root->player->player_y, verHitX, verHitY) : INT_MAX;

	// float foundHWallHit = root->map[(int)pos_h->y_pos /TILE_SIZE][(int)pos_h->x_pos / TILE_SIZE];
	// float foundVWallHit = root->map[(int)pos_v->y_pos /TILE_SIZE][(int)pos_v->x_pos / TILE_SIZE];
	// float horDistance = foundHWallHit ? distane_to_wall_temp(&(t_pos){*root->player->player_x, *root->player->player_y}, pos_h) : INT_MAX;
	// float verDistance = foundVWallHit ? distane_to_wall_temp(&(t_pos){*root->player->player_x, *root->player->player_y}, pos_v) : INT_MAX;
	if (verDistance < horDistance)
	{
		ray->distance = verDistance;
		ray->wallHitX = verHitX;
		ray->wallHitY = verHitY;
		ray->wallhircontent = verWallContent;
		// ray->wallHitX = pos_v->x_pos;
		// ray->wallHitY = pos_v->y_pos;
		// ray->wallhircontent = root->map[(int)pos_v->y_pos /TILE_SIZE][(int)pos_v->x_pos / TILE_SIZE];
		ray->WasHitVertical = true;
	}
	else
	{
		ray->distance = horDistance;
		ray->wallHitX = horHitX;
		ray->wallHitY = horHitY;
		ray->wallhircontent = horWallContent;
		// ray->wallHitX = pos_h->x_pos;
		// ray->wallHitY = pos_h->y_pos;
		// ray->wallhircontent = root->map[(int)pos_h->y_pos /TILE_SIZE][(int)pos_h->x_pos / TILE_SIZE];
		ray->WasHitVertical = false;
	}
	ray->facingDown = facingDown;
	ray->facingUp = facingUp;
	ray->facingRight = facingRight;
	ray->facingLeft = facingLeft;
	// render_ray(root, ray); // Render the ray for visualization
	return(ray);
}

// t_pos *calculate_distance(t_root *root, float rayangle, bool is_vertical) {
//     t_pos *res = create_pos();
//     if (!res) return NULL;
    
//     bool facingRight = (rayangle < M_PI_2 || rayangle > 3 * M_PI_2);
//     bool facingDown = (rayangle > 0 && rayangle < M_PI);
    
//     float intercept = floor((is_vertical ? *root->player->player_x : *root->player->player_y) / TILE_SIZE) * TILE_SIZE;
//     if ((is_vertical && facingRight) || (!is_vertical && facingDown))
//         intercept += TILE_SIZE;
    
//     float oppositeIntercept = (is_vertical) ?
//         *root->player->player_y + (intercept - *root->player->player_x) * tan(rayangle) :
//         *root->player->player_x + (intercept - *root->player->player_y) / tan(rayangle);
    
//     float step = TILE_SIZE * ((is_vertical && facingRight) || (!is_vertical && facingDown) ? 1 : -1);
//     float oppositeStep = TILE_SIZE * tan(rayangle);
//     if ((is_vertical && !facingRight && oppositeStep > 0) || (!is_vertical && !facingDown && oppositeStep > 0))
//         oppositeStep *= -1;
    
//     float nextX = is_vertical ? intercept : oppositeIntercept;
//     float nextY = is_vertical ? oppositeIntercept : intercept;
    
//     while (nextX >= 0 && nextX < root->win_w && nextY >= 0 && nextY < root->win_h) {
//         float checkX = nextX + (is_vertical ? -1 : 0);
//         float checkY = nextY + (!is_vertical ? -1 : 0);
        
//         if (maphaswallat(root, checkY, checkX)) {
//             res->x_pos = nextX;
//             res->y_pos = nextY;
//             return res;
//         }
//         nextX += step;
//         nextY += oppositeStep;
//     }
    
//     res->x_pos = -1;
//     res->y_pos = -1;
//     return res;
// }

// t_ray *cast_ray(t_root *root, t_ray *ray, float rayangle) {
//     rayangle = normalizeAngle(rayangle);
    
//     t_pos *pos_h = calculate_distance(root, rayangle, false);
//     t_pos *pos_v = calculate_distance(root, rayangle, true);
    
//     float horDistance = (pos_h && pos_h->x_pos >= 0) ? distance_to_wall(*root->player->player_x, *root->player->player_y, pos_h->x_pos, pos_h->y_pos) : INT_MAX;
//     float verDistance = (pos_v && pos_v->x_pos >= 0) ? distance_to_wall(*root->player->player_x, *root->player->player_y, pos_v->x_pos, pos_v->y_pos) : INT_MAX;
    
//     if (verDistance < horDistance) {
//         ray->distance = verDistance;
//         ray->wallHitX = pos_v->x_pos;
//         ray->wallHitY = pos_v->y_pos;
//         ray->wallhircontent = root->map[(int)(pos_v->y_pos / TILE_SIZE)][(int)(pos_v->x_pos / TILE_SIZE)];
//         ray->WasHitVertical = true;
//     } else {
//         ray->distance = horDistance;
//         ray->wallHitX = pos_h->x_pos;
//         ray->wallHitY = pos_h->y_pos;
//         ray->wallhircontent = root->map[(int)(pos_h->y_pos / TILE_SIZE)][(int)(pos_h->x_pos / TILE_SIZE)];
//         ray->WasHitVertical = false;
//     }
    
//     return ray;
// }




void cast_allRays(t_root *root)
{
	float rayangle = root->player->rotationAngle - (FOV / 2);
	t_ray rays[NUM_RAYS];
	int i = 0;
	while (i < NUM_RAYS)
	{
		cast_ray(root, &rays[i], rayangle, i);
		render_wall(root, &rays[i], i,rayangle);
		rayangle += FOV / NUM_RAYS;
		i++;
	}
}