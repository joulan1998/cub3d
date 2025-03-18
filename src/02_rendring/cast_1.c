/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-garr <ael-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 19:06:50 by ael-garr          #+#    #+#             */
/*   Updated: 2025/03/18 15:59:06 by ael-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../headers/cub3d.h"

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

t_i_infos	*create_info(t_root *root, float ang, bool ver)
{
	t_i_infos	*result;

	result = malloc(sizeof(t_i_infos) * 1);
	if (!result)
		return (NULL);
	result->angl = ang;
	result->p_x = (float)*root->player->player_x;
	result->p_y = (float)*root->player->player_y;
	result->ver = ver;
	return (result);
}

void	cal_intcep(float *x, float *y, t_i_infos *inf, t_compass *cmps)
{
	if (inf->ver)
	{
		*x = floor((inf->p_x / TILE_SIZE)) * TILE_SIZE;
		if (cmps->f_r)
			*x += TILE_SIZE;
		*y = inf->p_y + (*x - inf->p_x) * tan(inf->angl);
	}
	else
	{
		*y = floor(inf->p_y / TILE_SIZE) * TILE_SIZE;
		if (cmps->f_d)
			*y += TILE_SIZE;
		*x = inf->p_x + (*y - inf->p_y) / tan(inf->angl);
	}
	free(inf);
	free(cmps);
}

t_pos	*cal_v_d(t_root *root, float an, t_compass *cmps)
{
	float	ystep;
	t_pos	*dist;
	t_pos	*to_chek;

	to_chek = create_pos(0, 0);
	cal_intcep(&to_chek->x_pos, &to_chek->y_pos,
		create_info(root, an, true),
		create_compass(0, cmps->f_d, cmps->f_r, 0));
	ystep = TILE_SIZE * tan(an);
	if ((cmps->f_u && ystep > 0) || (cmps->f_d && ystep < 0))
		ystep *= -1;
	dist = create_pos(to_chek->x_pos, to_chek->y_pos);
	free(to_chek);
	return (return_pos_v(root, cmps, dist, ystep));
}
