/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-garr <ael-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 15:21:04 by ael-garr          #+#    #+#             */
/*   Updated: 2025/03/12 20:44:03 by ael-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

t_pos	*cal_h_d(t_root *root, float an, bool f_d, bool f_u, bool f_r, bool f_l)
{
	float	xstep;
	float	nexthtouchx;
	float	nexthtouchy;
	float	xtocheck;
	float	ytocheck;

	cal_intcep(&xtocheck, &ytocheck, *root->player->player_x, *root->player->player_y, an, 0, f_r, f_d);
	xstep = TILE_SIZE / tan(an);
	if ((f_l && xstep > 0) || (f_r && xstep < 0))
		xstep *= -1;
	nexthtouchx = xtocheck;
	nexthtouchy = ytocheck;
	while (nexthtouchx >= 0 && nexthtouchx < root->win_w && nexthtouchy >= 0 && nexthtouchy < root->win_h)
	{
		xtocheck = nexthtouchx;
		if (f_u)
			ytocheck = nexthtouchy - 1;
		else
			ytocheck = nexthtouchy;
		if (maphaswallat(root, ytocheck, xtocheck))
			return (create_pos(nexthtouchx, nexthtouchy));
		nexthtouchx += xstep;
		if (f_u)
			nexthtouchy -= TILE_SIZE;
		else
			nexthtouchy += TILE_SIZE;
	}
	return (create_pos(-1, -1));
}

void	set_ray_h(t_root *root, t_ray **ray, t_pos *pos)
{
	(*ray)->distance = distance_to_wall((float)*root->player->player_x,
			(float)*root->player->player_y, pos->x_pos, pos->y_pos);
	(*ray)->wallhitx = pos->x_pos;
	(*ray)->wallhity = pos->y_pos;
	(*ray)->wallhircontent = root->map[(int)(pos->y_pos / TILE_SIZE)]
	[(int)(pos->x_pos / TILE_SIZE)];
	(*ray)->wallhitvertical = true;
}

void	set_ray_v(t_root *root, t_ray **ray, t_pos *pos)
{
	(*ray)->distance = distance_to_wall
		((float)*root->player->player_x,
			(float)*root->player->player_y,
			pos->x_pos, pos->y_pos);
	(*ray)->wallhitx = pos->x_pos;
	(*ray)->wallhity = pos->y_pos;
	(*ray)->wallhircontent = root->map[(int)(pos->y_pos / TILE_SIZE)]
	[(int)(pos->x_pos / TILE_SIZE)];
	(*ray)->wallhitvertical = false;
}

t_ray	*cast_ray(t_root *root, t_ray *ray, float angl)
{
	t_pos	*h;
	t_pos	*v;

	angl = normalizeangle(angl);
	h = cal_h_d(root,
			angl, angl > 0 && angl < M_PI, !(angl > 0 && angl < M_PI),
			angl < M_PI_2 || angl > 3 * M_PI_2,
			!(angl < M_PI_2 || angl > 3 * M_PI_2));
	v = cal_v_d(root, angl,
			angl > 0 && angl < M_PI,
			!(angl > 0 && angl < M_PI), angl < M_PI_2 || angl > 3 * M_PI_2,
			!(angl < M_PI_2 || angl > 3 * M_PI_2));
	if (v && v->x_pos >= 0 && (!h || h->x_pos < 0
			|| distance_to_wall((float)*root->player->player_x,
				(float)*root->player->player_y, v->x_pos, v->y_pos)
			< distance_to_wall((float)*root->player->player_x,
				(float)*root->player->player_y, h->x_pos, h->y_pos)))
		set_ray_h(root, &ray, v);
	else if (h && h->x_pos >= 0)
		set_ray_v(root, &ray, h);
	return (ray);
}

void	cast_allrays(t_root *root)
{
	int		i;
	float	angl;
	t_ray	rays[NUM_RAYS];

	angl = root->player->rot_angl - (FOV / 2);
	i = 0;
	while (i < NUM_RAYS)
	{
		cast_ray(root, &rays[i], angl);
		render_wall(root, &rays[i], i, angl);
		angl += FOV / NUM_RAYS;
		i++;
	}
}
