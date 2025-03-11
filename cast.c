/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-garr <ael-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 15:21:04 by ael-garr          #+#    #+#             */
/*   Updated: 2025/03/11 13:45:58 by ael-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	render_ray(t_root *root, t_ray *ray)
{
	draw_line(root, *root->player->player_y, *root->player->player_x,
		ray->wallHitY, ray->wallHitX, GREEN);
}

int	distane_to_wall_temp(t_pos *pos1, t_pos *pos2)
{
	return (sqrt((pos2->x_pos - pos1->x_pos)
		* (pos2->x_pos - pos1->x_pos) + (pos2->y_pos - pos1->y_pos)
		* (pos2->y_pos - pos1->y_pos)));
}

int	distance_to_wall(float x1, float y1, float x2, float y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

float	normalizeangle(float angle)
{
	float	res;

	res = fmod(angle, (M_PI * 2));
	if (res < 0)
		res = (2 * M_PI) + res;
	return (res);
}

t_pos	*create_pos(void)
{
	t_pos *res;
	res = malloc(sizeof(t_pos));
	if (!res)
		return (0);
	return (res);
}

t_pos *calculate_vertical_intersection(t_root *root, float rayangle, bool facingDown, bool facingUp, bool facingRight, bool facingleft)
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
	xstep = TILE_SIZE * (facingleft ? -1 : 1);
	ystep = TILE_SIZE * tan(rayangle);
	if ((facingUp && ystep > 0) || (facingDown && ystep < 0)) ystep *= -1;
	nextVtouchX = xintercept;
	nextVtouchY = yintercept;
	result = create_pos();
	while (nextVtouchX >= 0 && nextVtouchX < root->win_w && nextVtouchY >= 0 && nextVtouchY < root->win_h)
	{
		xtocheck = nextVtouchX + (facingleft ? -1 : 0);
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
	return (result);
}

t_pos	*calculate_horizontal_intersection(t_root *root, float rayangle, bool facingDown, bool facingUp, bool facingRight, bool facingleft)
{
	t_pos	*result;
	float	yintercept;
	float	xintercept;
	float	ystep;
	float	xstep;
	float	nexthtouchx;
	float	nexthtouchy;
	float	xtocheck;
	float	ytocheck;

	result = create_pos();
	yintercept = floor(*root->player->player_y / TILE_SIZE) * TILE_SIZE;
	yintercept += facingDown ? TILE_SIZE : 0;
	xintercept = *root->player->player_x + (yintercept - *root->player->player_y) / tan(rayangle);
	ystep = TILE_SIZE * (facingUp ? -1 : 1);
	xstep = TILE_SIZE / tan(rayangle);
	if ((facingleft && xstep > 0) || (facingRight && xstep < 0))
	xstep *= -1;
	nexthtouchx = xintercept;
	nexthtouchy = yintercept;
	while (nexthtouchx >= 0 && nexthtouchx < root->win_w && nexthtouchy >= 0 && nexthtouchy < root->win_h)
	{
		xtocheck = nexthtouchx;
		ytocheck = nexthtouchy + (facingUp ? -1 : 0);
		if (maphaswallat(root, ytocheck, xtocheck))
		{
			result->x_pos = (float)nexthtouchx;
			result->y_pos = (float)nexthtouchy;
			return result;
		}
		nexthtouchx += xstep;
		nexthtouchy += ystep;
	}
	return (result);
}

t_ray *cast_ray(t_root *root, t_ray *ray, float rayangle)
{	
	bool	facingdown;
	bool	facingup;
	bool	facingright;
	bool	facingleft;
	float	hordistance;
	float	verdistance;
	t_pos	*pos_h;
	t_pos	*pos_v;

	rayangle = normalizeangle(rayangle);
	facingdown = rayangle > 0 && rayangle < M_PI;
	facingup = !facingdown;
	facingright = rayangle < M_PI_2 || rayangle > 3 * M_PI_2;
	facingleft = !facingright;
	pos_h = calculate_horizontal_intersection
		(root, rayangle, facingdown, facingup, facingright, facingleft);
	pos_v = calculate_vertical_intersection
		(root, rayangle, facingdown, facingup, facingright, facingleft);
	if (pos_h && pos_h->x_pos >= 0)
		hordistance = distance_to_wall((float)*root->player->player_x, (float)*root->player->player_y, pos_h->x_pos, pos_h->y_pos);
	else
		hordistance = INT_MAX;
	if (pos_v && pos_v->x_pos >= 0)
		verdistance = distance_to_wall((float)*root->player->player_x, (float)*root->player->player_y, pos_v->x_pos, pos_v->y_pos);
	else
		verdistance = INT_MAX;
	if (verdistance < hordistance)
	{
		ray->distance = verdistance;
		ray->wallHitX = pos_v->x_pos;
		ray->wallHitY = pos_v->y_pos;
		ray->wallhircontent = root->map[(int)(pos_v->y_pos / TILE_SIZE)][(int)(pos_v->x_pos / TILE_SIZE)];
		ray->WasHitVertical = true;
	}
	else
	{
		ray->distance = hordistance;
		ray->wallHitX = pos_h->x_pos;
		ray->wallHitY = pos_h->y_pos;
		ray->wallhircontent = root->map[(int)(pos_h->y_pos / TILE_SIZE)][(int)(pos_h->x_pos / TILE_SIZE)];
		ray->WasHitVertical = false;
	}
	return (ray);
}

void	cast_allrays(t_root *root)
{
	int		i;
	float	rayangle;
	t_ray	rays[NUM_RAYS];

	rayangle = root->player->rotationAngle - (FOV / 2);
	i = 0;
	while (i < NUM_RAYS)
	{
		// cast_ray(root, &rays[i], rayangle/*, i*/);
		cast_ray(root, &rays[i], rayangle);
		render_wall(root, &rays[i], i, rayangle);
		rayangle += FOV / NUM_RAYS;
		i++;
	}
}
