/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-garr <ael-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 15:21:04 by ael-garr          #+#    #+#             */
/*   Updated: 2025/03/13 17:19:48 by ael-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

t_pos	*cal_h_d(t_root *root, float an, t_compass *cmps)
{
	float	xstep;
	float	n_h_t_x;
	float	n_h_t_y;
	float	x_chk;
	float	y_chk;

	cal_intcep(&x_chk, &y_chk, *root->player->player_x, *root->player->player_y, an, 0, create_compass(0, cmps->f_d, cmps->f_r, 0));
	xstep = TILE_SIZE / tan(an);
	if ((cmps->f_l && xstep > 0) || (cmps->f_r && xstep < 0))
		xstep *= -1;
	n_h_t_x = x_chk;
	n_h_t_y = y_chk;
	while (n_h_t_x >= 0 && n_h_t_x < root->win_w && n_h_t_y >= 0 && n_h_t_y < root->win_h)
	{
		x_chk = n_h_t_x;
		if (cmps->f_u)
			y_chk = n_h_t_y - 1;
		else
			y_chk = n_h_t_y;
		if (maphaswallat(root, y_chk, x_chk))
			return (create_pos(n_h_t_x, n_h_t_y));
		n_h_t_x += xstep;
		if (cmps->f_u)
			n_h_t_y -= TILE_SIZE;
		else
			n_h_t_y += TILE_SIZE;
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
	h = cal_h_d(root, angl,
			create_compass(!(angl > 0 && angl < M_PI),
				angl > 0 && angl < M_PI,
				angl < M_PI_2 || angl > 3 * M_PI_2,
				!(angl < M_PI_2 || angl > 3 * M_PI_2)));
	v = cal_v_d(root, angl,
			create_compass(!(angl > 0 && angl < M_PI),
				angl > 0 && angl < M_PI,
				angl < M_PI_2 || angl > 3 * M_PI_2,
				!(angl < M_PI_2 || angl > 3 * M_PI_2)));
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
