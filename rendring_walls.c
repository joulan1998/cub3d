/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendring_walls.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-garr <ael-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 16:23:34 by ael-garr          #+#    #+#             */
/*   Updated: 2025/03/24 14:45:37 by ael-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	decide_txt(t_root *root, t_rndr_str *rndr, t_ray *ray, t_mlx **txt)
{
	if (ray->wallhitvertical)
	{
		if (ray->facingleft)
			*txt = &root->left_wall_texture;
		else
			*txt = &root->right_wall_texture;
		rndr->wall_x = ray->wallhity
			- floor(ray->wallhity / TILE_SIZE) * TILE_SIZE;
	}
	else
	{
		if (ray->facingup)
			*txt = &root->front_wall_texture;
		else
			*txt = &root->back_wall_texture;
		rndr->wall_x = ray->wallhitx
			- floor(ray->wallhitx / TILE_SIZE) * TILE_SIZE;
	}
}

t_rndr_str	*crt_rnd_str(t_root *root, t_ray *ray, float anglee, t_mlx **txt)
{
	t_rndr_str	*res;
	float		walltop;
	float		wallbottom;

	res = malloc(sizeof(t_rndr_str));
	if (!res)
		return (NULL);
	res->perp_dist = ray->distance
		* cos((double)(anglee - root->player->rot_angl));
	if (res->perp_dist <= 0.0f)
		res->perp_dist = 0.1f;
	res->distanceprojwall = (root->win_w / 2) / tan((60 * (M_PI / 180)) / 2);
	res->projwallheight = (TILE_SIZE / res->perp_dist) * res->distanceprojwall;
	if (res->projwallheight > INT_MAX / 2)
		res->projwallheight = root->win_h;
	res->wallstripeheight = (int)res->projwallheight;
	walltop = (root->win_h / 2.0f) - (res->wallstripeheight / 2.0f);
	wallbottom = (root->win_h / 2.0f) + (res->wallstripeheight / 2.0f);
	res->walltoppixel = (int)fmaxf(0.0f, walltop);
	res->wallbottompixel = (int)fminf((float)root->win_h, wallbottom);
	if (res->wallbottompixel <= res->walltoppixel)
		res->wallbottompixel = res->walltoppixel + 1;
	decide_txt(root, res, ray, txt);
	return (res);
}

void	set_tex_x(t_root *root, float *x, t_rndr_str *rndr, t_mlx *tex)
{
	*x = (int)(rndr->wall_x * tex->width / TILE_SIZE);
	if (*x < 0)
		*x = 0;
	if (*x >= tex->width)
		*x = tex->width - 1;
}

void	draw_wall_strp(t_root *root, t_rndr_str *rndr, int strip_id, t_mlx *txt)
{
	float	tex_x;
	float	tex_y;
	float	tex_pos;
	int		y;
	int		color;

	set_tex_x(root, &tex_x, rndr, txt);
	tex_pos = 0;
	y = -1;
	while (y++ < rndr->walltoppixel)
		my_mlx_pixel_put(&root->mlx_img, strip_id, y, root->ceiling_color);
	y = rndr->walltoppixel;
	while (y < rndr->wallbottompixel)
	{
		tex_y = (int)tex_pos;
		if (tex_y >= txt->height)
			tex_y = txt->height - 1;
		color = *(int *)(txt->addr + (int)(tex_y * txt->line_length
					+ tex_x * (txt->bits_per_pixel / 8)));
		my_mlx_pixel_put(&root->mlx_img, strip_id, y++, color);
		tex_pos += (float)txt->height / rndr->wallstripeheight;
	}
	y = rndr->wallbottompixel;
	while (y < root->win_h)
		my_mlx_pixel_put(&root->mlx_img, strip_id, y++, root->floor_color);
}

void	render_wall(t_root *root, t_ray *ray, int strip_id, float anglee)
{
	t_mlx		*txt;
	t_rndr_str	*rndr;

	rndr = crt_rnd_str(root, ray, anglee, &txt);
	if (!rndr)
		return ;
	draw_wall_strp(root, rndr, strip_id, txt);
	free(rndr);
}
