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

t_pos *calculate_vertical_intersection(t_root *root, float rayangle, bool facingDown, bool facingUp, bool facingRight, bool facingLeft)
{
	t_pos	*result;
	float	xintercept;
	float	yintercept;
	float	ystep;
	float	xstep;
	float	nextVtouchX;
	float	nextVtouchY;
	float	xtocheck;
	float	ytocheck;

	xintercept = floor(*root->player->player_x / TILE_SIZE) * TILE_SIZE;
	xintercept += facingRight ? TILE_SIZE : 0;
	yintercept = *root->player->player_y + (xintercept - *root->player->player_x) * tan(rayangle);
	xstep = TILE_SIZE * (facingLeft ? -1 : 1);
	ystep = TILE_SIZE * tan(rayangle);
	if ((facingUp && ystep > 0) || (facingDown && ystep < 0)) ystep *= -1;
	nextVtouchX = xintercept;
	nextVtouchY = yintercept;
	result = create_pos();
	while (nextVtouchX >= 0 && nextVtouchX < root->win_w && nextVtouchY >= 0 && nextVtouchY < root->win_h)
	{
		xtocheck = nextVtouchX + (facingLeft ? -1 : 0);
		ytocheck = nextVtouchY;
		if (maphaswallat(root, ytocheck, xtocheck))
		{
			result->x_pos = (float)nextVtouchX;
			result->y_pos = (float)nextVtouchY;
			return result;
		}
		nextVtouchX += xstep;
		nextVtouchY += ystep;
	}
	return result;
}

t_pos *calculate_horizontal_intersection(t_root *root, float rayangle, bool facingDown, bool facingUp, bool facingRight, bool facingLeft)
{
	t_pos	*result;
	float	yintercept;
	float	xintercept;
	float	ystep;
	float	xstep;
	float	nextHtouchX;
	float	nextHtouchY;
	float	xtocheck;
	float	ytocheck;

	result = create_pos();
	yintercept = floor(*root->player->player_y / TILE_SIZE) * TILE_SIZE;
	yintercept += facingDown ? TILE_SIZE : 0;
	xintercept = *root->player->player_x + (yintercept - *root->player->player_y) / tan(rayangle);
	ystep = TILE_SIZE * (facingUp ? -1 : 1);
	xstep = TILE_SIZE / tan(rayangle);
	if ((facingLeft && xstep > 0) || (facingRight && xstep < 0))
	xstep *= -1;
	nextHtouchX = xintercept;
	nextHtouchY = yintercept;
	while (nextHtouchX >= 0 && nextHtouchX < root->win_w && nextHtouchY >= 0 && nextHtouchY < root->win_h)
	{
		xtocheck = nextHtouchX;
		ytocheck = nextHtouchY + (facingUp ? -1 : 0);
		if (maphaswallat(root, ytocheck, xtocheck))
		{
			result->x_pos = (float)nextHtouchX;
			result->y_pos = (float)nextHtouchY;
			return result;
		}
		nextHtouchX += xstep;
		nextHtouchY += ystep;
	}
	return result;
}

t_ray *cast_ray(t_root *root, t_ray *ray, float rayangle)
{	
	bool	facingDown;
	bool	facingUp;
	bool	facingRight;
	bool	facingLeft;
	float	horDistance;
	float	verDistance;
	t_pos	*pos_h;
	t_pos	*pos_v;

	rayangle = normalizeAngle(rayangle);
	facingDown = rayangle > 0 && rayangle < M_PI;
	facingUp = !facingDown;
	facingRight = rayangle < M_PI_2 || rayangle > 3 * M_PI_2;
	facingLeft = !facingRight;
	pos_h = calculate_horizontal_intersection(root, rayangle, facingDown, facingUp, facingRight,facingLeft);
	pos_v = calculate_vertical_intersection(root, rayangle, facingDown, facingUp, facingRight,facingLeft);
	horDistance = (pos_h && pos_h->x_pos >= 0) ? distance_to_wall((float)*root->player->player_x, (float)*root->player->player_y, pos_h->x_pos, pos_h->y_pos) : INT_MAX;
	verDistance = (pos_v && pos_v->x_pos >= 0) ? distance_to_wall((float)*root->player->player_x, (float)*root->player->player_y, pos_v->x_pos, pos_v->y_pos) : INT_MAX;
	if (verDistance < horDistance)
	{
		ray->distance = verDistance;
		ray->wallHitX = pos_v->x_pos;
		ray->wallHitY = pos_v->y_pos;
		ray->wallhircontent = root->map[(int)(pos_v->y_pos / TILE_SIZE)][(int)(pos_v->x_pos / TILE_SIZE)];
		ray->WasHitVertical = true;
	}
	else
	{
		ray->distance = horDistance;
		ray->wallHitX = pos_h->x_pos;
		ray->wallHitY = pos_h->y_pos;
		ray->wallhircontent = root->map[(int)(pos_h->y_pos / TILE_SIZE)][(int)(pos_h->x_pos / TILE_SIZE)];
		ray->WasHitVertical = false;
	}
	return ray;
}

void cast_allRays(t_root *root)
{
	float rayangle = root->player->rotationAngle - (FOV / 2);
	t_ray rays[NUM_RAYS];
	int i = 0;
	while (i < NUM_RAYS)
	{
		// cast_ray(root, &rays[i], rayangle, i);
		cast_ray(root, &rays[i], rayangle);
		render_wall(root, &rays[i], i,rayangle);
		rayangle += FOV / NUM_RAYS;
		i++;
	}
}