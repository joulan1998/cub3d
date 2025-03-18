/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-garr <ael-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 15:21:04 by ael-garr          #+#    #+#             */
/*   Updated: 2025/03/17 19:36:05 by ael-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../headers/cub3d.h"

t_pos	*cal_h_d(t_root *root, float an, t_compass *cmps)
{
	float	xstep;
	t_pos	*dist;
	t_pos	*to_chek;

	to_chek = create_pos(0, 0);
	cal_intcep(&to_chek->x_pos, &to_chek->y_pos,
		create_info(root, an, false),
		create_compass(0, cmps->f_d, cmps->f_r, 0));
	xstep = TILE_SIZE / tan(an);
	if ((cmps->f_l && xstep > 0) || (cmps->f_r && xstep < 0))
		xstep *= -1;
	dist = create_pos(to_chek->x_pos, to_chek->y_pos);
	free(to_chek);
	return (return_pos_h(root, cmps, dist, xstep));
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
	if (v && v->x_pos >= 0 && (!h || h->x_pos < 0 || distance_to_wall(
				(float)*root->player->player_x,
				(float)*root->player->player_y, v->x_pos, v->y_pos)
			< distance_to_wall((float)*root->player->player_x,
				(float)*root->player->player_y, h->x_pos, h->y_pos)))
		set_ray_h(root, &ray, v);
	else
		set_ray_v(root, &ray, h);
	free(h);
	free(v);
	return (ray);
}

void	cast_allrays(t_root *root)
{
	int		i;
	float	angl;
	t_ray	rays[NUM_RAYS];
	float	fov;

	fov = (60 *(M_PI / 180));
	angl = root->player->rot_angl - (fov / 2);
	i = 0;
	while (i < NUM_RAYS)
	{
		cast_ray(root, &rays[i], angl);
		render_wall(root, &rays[i], i, angl);
		angl += fov / NUM_RAYS;
		i++;
	}
}
