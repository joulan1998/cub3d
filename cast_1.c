/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-garr <ael-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 19:06:50 by ael-garr          #+#    #+#             */
/*   Updated: 2025/03/12 19:43:37 by ael-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

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

t_pos	*create_pos(float x, float y)
{
	t_pos	*pos;

	pos = (t_pos *)malloc(sizeof(t_pos));
	pos->x_pos = x;
	pos->y_pos = y;
	return (pos);
}

void	cal_intcep(float *x, float *y, float p_x, float p_y, float angle, bool ver, bool f_r, bool f_d)
{
	if (ver)
	{
		*x = floor(p_x / TILE_SIZE) * TILE_SIZE;
		if (f_r)
			*x += TILE_SIZE;
		*y = p_y + (*x - p_x) * tan(angle);
	}
	else
	{
		*y = floor(p_y / TILE_SIZE) * TILE_SIZE;
		if (f_d)
			*y += TILE_SIZE;
		*x = p_x + (*y - p_y) / tan(angle);
	}
}

t_pos	*cal_v_d(t_root *root, float an, bool f_d, bool f_u, bool f_r, bool f_l)
{
	float	xintercept;
	float	yintercept;
	float	xstep;
	float	ystep;
	float	n_v_t_h;
	float	n_v_t_y;
	float	xtocheck;
	float	ytocheck;

	cal_intcep(&xintercept, &yintercept, *root->player->player_x, *root->player->player_y, an, true, f_r, f_d);
	xstep = TILE_SIZE * (f_l ? -1 : 1);
	ystep = TILE_SIZE * tan(an);
	if ((f_u && ystep > 0) || (f_d && ystep < 0))
		ystep *= -1;
	n_v_t_h = xintercept;
	n_v_t_y = yintercept;
	while (n_v_t_h >= 0 && n_v_t_h < root->win_w && n_v_t_y >= 0 && n_v_t_y < root->win_h)
	{
		xtocheck = n_v_t_h + (f_l ? -1 : 0);
		ytocheck = n_v_t_y;
		if (maphaswallat(root, ytocheck, xtocheck))
			return (create_pos(n_v_t_h, n_v_t_y));
		n_v_t_h += xstep;
		n_v_t_y += ystep;
	}
	return (create_pos(-1, -1));
}
