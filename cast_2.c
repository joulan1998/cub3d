/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-garr <ael-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 19:34:29 by ael-garr          #+#    #+#             */
/*   Updated: 2025/03/17 19:42:26 by ael-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

t_pos	*return_pos_v(t_root *root, t_compass *cmps, t_pos *dist, float ystep)
{
	t_pos	*to_chek;
	t_pos	*res;

	to_chek = create_pos(0, 0);
	while (dist->x_pos >= 0 && dist->x_pos < root->win_w
		&& dist->y_pos >= 0 && dist->y_pos < root->win_h)
	{
		to_chek->y_pos = dist->y_pos;
		if (cmps->f_l)
			to_chek->x_pos = dist->x_pos - 1;
		else
			to_chek->x_pos = dist->x_pos;
		if (maphaswallat(root, to_chek->y_pos, to_chek->x_pos))
		{
			res = create_pos(dist->x_pos, dist->y_pos);
			return (free(to_chek), free(cmps), free(dist), res);
		}
		if (cmps->f_l)
			dist->x_pos -= TILE_SIZE;
		else
			dist->x_pos += TILE_SIZE;
		dist->y_pos += ystep;
	}
	res = create_pos(-1, -1);
	return (free(to_chek), free(cmps), free(dist), res);
}

t_pos	*create_pos(float x, float y)
{
	t_pos	*pos;

	pos = (t_pos *)malloc(sizeof(t_pos));
	pos->x_pos = x;
	pos->y_pos = y;
	return (pos);
}

t_pos	*return_pos_h(t_root *root, t_compass *cmps, t_pos *dist, float xstep)
{
	t_pos	*to_chek;
	t_pos	*res;

	to_chek = create_pos(0, 0);
	while (dist->x_pos >= 0 && dist->x_pos < root->win_w
		&& dist->y_pos >= 0 && dist->y_pos < root->win_h)
	{
		to_chek->x_pos = dist->x_pos;
		if (cmps->f_u)
			to_chek->y_pos = dist->y_pos - 1;
		else
			to_chek->y_pos = dist->y_pos;
		if (maphaswallat(root, to_chek->y_pos, to_chek->x_pos))
		{
			res = create_pos(dist->x_pos, dist->y_pos);
			return (free(to_chek), free(cmps), free(dist), res);
		}
		dist->x_pos += xstep;
		if (cmps->f_u)
			dist->y_pos -= TILE_SIZE;
		else
			dist->y_pos += TILE_SIZE;
	}
	res = create_pos(-1, -1);
	return (free(to_chek), free(cmps), free(dist), res);
}
