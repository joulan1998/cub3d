/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendring_walls.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-garr <ael-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 16:23:34 by ael-garr          #+#    #+#             */
/*   Updated: 2025/03/17 20:15:20 by ael-garr         ###   ########.fr       */
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
		rndr->wall_x = ray->wallhity - floor(ray->wallhity / TILE_SIZE) * TILE_SIZE;
	}
	else
	{
		if (ray->facingup)
			*txt = &root->front_wall_texture;
		else
			*txt = &root->back_wall_texture;
		rndr->wall_x = ray->wallhitx - floor(ray->wallhitx / TILE_SIZE) * TILE_SIZE;
	}
}

t_rndr_str	*crt_rnd_str(t_root *root, t_ray *ray, float anglee, t_mlx **txt)
{
	t_rndr_str	*res;

	res = malloc(sizeof(t_rndr_str));
	if (!res)
		return (NULL);
	res->perp_dist = ray->distance * cos((double)(anglee - root->player->rot_angl));
	res->distanceprojwall = (root->win_w / 2) / tan((60 * (M_PI / 180)) / 2);
	res->projwallheight = (TILE_SIZE / res->perp_dist) * res->distanceprojwall;
	res->wallstripeheight = (int)res->projwallheight;
	res->walltoppixel = (root->win_h / 2) - (res->wallstripeheight / 2);
	res->wallbottompixel = (root->win_h / 2) + (res->wallstripeheight / 2);
	if (res->walltoppixel < 0)
		res->walltoppixel = 0;
	if (res->wallbottompixel > root->win_h)
		res->wallbottompixel = root->win_h;
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

void	draw_wall_strip(t_root *root, t_rndr_str *rndr, int strip_id, t_mlx *texture)
{
	float	tex_x;
	float	tex_y;
	// float	tex_step;
	float	tex_pos;
	int		y;
	int		color;

	// tex_x = (int)(rndr->wall_x * texture->width / TILE_SIZE);
	// if (tex_x < 0)
	// 	tex_x = 0;
	// if (tex_x >= texture->width)
	// 	tex_x = texture->width - 1;
	set_tex_x(root, &tex_x, rndr, texture);
	// tex_step = (float)texture->height / rndr->wallstripeheight;
	tex_pos = 0;
	y = 0;
	while (y < rndr->walltoppixel)
		my_mlx_pixel_put(&root->mlx_img, strip_id, y++, BLUE);
	y = rndr->walltoppixel;
	while (y < rndr->wallbottompixel)
	{
		tex_y = (int)tex_pos;
		if (tex_y >= texture->height)
			tex_y = texture->height - 1;
		color = *(int *)(texture->addr + (int)(tex_y * texture->line_length + tex_x * (texture->bits_per_pixel / 8)));
		my_mlx_pixel_put(&root->mlx_img, strip_id, y++, color);
		// tex_pos += tex_step;
		tex_pos += (float)texture->height / rndr->wallstripeheight;
	}
	y = rndr->wallbottompixel;
	while (y < root->win_h)
		my_mlx_pixel_put(&root->mlx_img, strip_id, y++, GREEN);
}

void	render_wall(t_root *root, t_ray *ray, int strip_id, float anglee)
{
	t_mlx		*texture;
	t_rndr_str	*rndr;

	rndr = crt_rnd_str(root, ray, anglee, &texture);
	if (!rndr)
		return ;
	draw_wall_strip(root, rndr, strip_id, texture);
	free(rndr);
}
