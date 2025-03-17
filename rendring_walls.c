/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendring_walls.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-garr <ael-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 16:23:34 by ael-garr          #+#    #+#             */
/*   Updated: 2025/03/17 15:30:31 by ael-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

t_rndr_str *crt_rnd_str(t_root *root, t_ray *ray, float anglee, t_mlx **txt)
{
	t_rndr_str *res;

	res = malloc(sizeof(t_rndr_str));
	if (!res)
		return (NULL);
	res->perp_dist = ray->distance * cos((double)(anglee - root->player->rot_angl));
	res->distanceprojwall = (root->win_w / 2) / tan(FOV / 2);
	res->projwallheight = (TILE_SIZE / res->perp_dist) * res->distanceprojwall;
	res->wallstripeheight = (int)res->projwallheight;
	res->walltoppixel = (root->win_h / 2) - (res->wallstripeheight / 2);
	res->wallbottompixel = (root->win_h / 2) + (res->wallstripeheight / 2);
	if (res->walltoppixel < 0) res->walltoppixel = 0;
	if (res->wallbottompixel > root->win_h) res->wallbottompixel = root->win_h;
	if (ray->wallhitvertical)
	{
		if (ray->facingleft)
			*txt = &root->left_wall_texture;
		else
			*txt = &root->right_wall_texture;
		res->wall_x = ray->wallhity - floor(ray->wallhity / TILE_SIZE) * TILE_SIZE;
	}
	else
	{
		if (ray->facingup)
			*txt = &root->front_wall_texture;
		else
			*txt = &root->back_wall_texture;
		res->wall_x = ray->wallhitx - floor(ray->wallhitx / TILE_SIZE) * TILE_SIZE;
	}
	return (res);
}



void	final_draw(t_root *root, t_rndr_str *rndr, int strip_id, t_mlx **texture)
{
	int y;
	int tex_x;
	int tex_y;
	// int tex_pos;
	int tex_step;
	int tex_pos;
	
	tex_x = (int)(rndr->wall_x * (*texture)->width / TILE_SIZE);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= (*texture)->width)
		tex_x = (*texture)->width - 1;
	tex_pos = 0;
	tex_step = (float)((*texture))->height / rndr->wallstripeheight;
	y = 0;
	while ( y < rndr->walltoppixel)
		my_mlx_pixel_put(&root->mlx_img, strip_id, y++, BLUE);
	y = rndr->walltoppixel;
	while (y < rndr->wallbottompixel)
	{
		tex_y = (int)tex_pos;
		if (tex_y >= ((*texture))->height)
			tex_y = ((*texture))->height - 1;
		int color = *(int *)(((*texture))->addr + (tex_y * ((*texture))->line_length + tex_x * (((*texture))->bits_per_pixel / 8)));
		my_mlx_pixel_put(&root->mlx_img, strip_id, y++, color);
		tex_pos += tex_step;
	}
	y = rndr->wallbottompixel;
	while (y < root->win_h)
		my_mlx_pixel_put(&root->mlx_img, strip_id, y++, GREEN);
}

// void final_draw(t_root *root, t_rndr_str *rndr, int strip_id, t_mlx *texture)
// {
// 	int y;
// 	int tex_x;
// 	int tex_y;
// 	float tex_step;
// 	float tex_pos;

// 	// Validate texture pointer
// 	if (!texture || !texture->addr)
// 	{
// 		printf("Error: Invalid texture pointer or texture data.\n");
// 		return;
// 	}

// 	// Calculate texture x-coordinate (offset)
// 	tex_x = (int)(rndr->wall_x * texture->width / TILE_SIZE);
// 	tex_x = (tex_x < 0) ? 0 : (tex_x >= texture->width) ? texture->width - 1 : tex_x;

// 	// Calculate texture step and starting position
// 	tex_step = (float)texture->height / rndr->wallstripeheight;
// 	if (tex_step < 1.0f)
// 		tex_step = 1.0f; // Ensure at least 1 pixel step

// 	tex_pos = (rndr->walltoppixel - root->win_h / 2 + rndr->wallstripeheight / 2) * tex_step;

// 	// Render ceiling
// 	y = 0;
// 	while (y < rndr->walltoppixel)
// 		my_mlx_pixel_put(&root->mlx_img, strip_id, y++, BLUE);

// 	// Render wall using texture
// 	y = rndr->walltoppixel;
// 	while (y < rndr->wallbottompixel)
// 	{
// 		tex_y = (int)tex_pos;
// 		tex_y = (tex_y < 0) ? 0 : (tex_y >= texture->height) ? texture->height - 1 : tex_y;

// 		int color = *(int *)(texture->addr + (tex_y * texture->line_length + tex_x * (texture->bits_per_pixel / 8)));
// 		my_mlx_pixel_put(&root->mlx_img, strip_id, y++, color);

// 		tex_pos += tex_step; // Move to the next texture row
// 	}

// 	// Render floor
// 	y = rndr->wallbottompixel;
// 	while (y < root->win_h)
// 		my_mlx_pixel_put(&root->mlx_img, strip_id, y++, GREEN);
// }

// void final_draw(t_root *root, t_rndr_str *rndr, int strip_id, t_mlx *texture)
// {
// 	int y;
// 	int tex_x;
// 	int tex_y;
// 	float tex_step;
// 	float tex_pos;

// 	// Validate texture pointer
// 	if (!texture || !texture->addr)
// 	{
// 		printf("Error: Invalid texture pointer or texture data.\n");
// 		return;
// 	}

// 	// Calculate texture x-coordinate (offset)
// 	tex_x = (int)(rndr->wall_x * texture->width / TILE_SIZE);
// 	tex_x = (tex_x < 0) ? 0 : (tex_x >= texture->width) ? texture->width - 1 : tex_x;

// 	// Calculate texture step and starting position
// 	tex_step = (float)texture->height / rndr->wallstripeheight;
// 	if (tex_step < 1.0f)
// 		tex_step = 1.0f; // Ensure at least 1 pixel step
// 	if (tex_step > texture->height)
// 		tex_step = texture->height; // Avoid excessive stepping

// 	tex_pos = (rndr->walltoppixel - root->win_h / 2 + rndr->wallstripeheight / 2) * tex_step;

// 	// Render ceiling
// 	y = 0;
// 	while (y < rndr->walltoppixel)
// 		my_mlx_pixel_put(&root->mlx_img, strip_id, y++, BLUE);

// 	// Render wall using texture
// 	y = rndr->walltoppixel;
// 	while (y < rndr->wallbottompixel)
// 	{
// 		tex_y = (int)tex_pos;
// 		tex_y = (tex_y < 0) ? 0 : (tex_y >= texture->height) ? texture->height - 1 : tex_y;

// 		int color = *(int *)(texture->addr + (tex_y * texture->line_length + tex_x * (texture->bits_per_pixel / 8)));
// 		my_mlx_pixel_put(&root->mlx_img, strip_id, y++, color);

// 		tex_pos += tex_step; // Move to the next texture row
// 	}

// 	// Render floor
// 	y = rndr->wallbottompixel;
// 	while (y < root->win_h)
// 		my_mlx_pixel_put(&root->mlx_img, strip_id, y++, GREEN);
// }
// void final_draw(t_root *root, t_rndr_str *rndr, int strip_id, t_mlx *texture)
// {
// 	int y;
// 	int tex_x;
// 	int tex_y;
// 	int tex_step;
// 	int tex_pos;

// 	if (!texture || !texture->addr)
// 	{
// 		printf("Error: Invalid texture pointer or texture data.\n");
// 		return;
// 	}
// 	tex_x = (int)(rndr->wall_x * texture->width / TILE_SIZE);
// 	if (tex_x < 0)
// 		tex_x = 0;
// 	if (tex_x >= texture->width)
// 		tex_x = texture->width - 1;
// 	tex_step = (float)texture->height / rndr->wallstripeheight;
// 	tex_pos = 0;
// 	y = 0;
// 	while (y < rndr->walltoppixel)
// 		my_mlx_pixel_put(&root->mlx_img, strip_id, y++, BLUE);
// 	y = rndr->walltoppixel;
// 	while (y < rndr->wallbottompixel)
// 	{
// 		tex_y = (int)tex_pos;
// 		if (tex_y < 0)
// 			tex_y = 0;
// 		if (tex_y >= texture->height)
// 			tex_y = texture->height - 1;
// 		int color = *(int *)(texture->addr + (tex_y * texture->line_length + tex_x * (texture->bits_per_pixel / 8)));
// 		my_mlx_pixel_put(&root->mlx_img, strip_id, y++, color);
// 		tex_pos += tex_step;
// 	}
// 	y = rndr->wallbottompixel;
// 	while (y < root->win_h)
// 		my_mlx_pixel_put(&root->mlx_img, strip_id, y++, GREEN);
// }

void	coloring(t_root *root, t_ray *ray,int strip_id, float anglee, t_mlx *texture,t_rndr_str *rndr)
{
	int y;
	int tex_pos = 0;
	int tex_y;
	y = rndr->walltoppixel;
	float tex_step = (float)texture->height / rndr->wallstripeheight;
	int tex_x = (int)(rndr->wall_x * texture->width / TILE_SIZE);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= texture->width)
		tex_x = texture->width - 1;
	while (y < rndr->wallbottompixel)
	{
		tex_y = (int)tex_pos;
		if (tex_y >= texture->height)
			tex_y = texture->height - 1;
		int color = *(int *)(texture->addr + (tex_y * texture->line_length + tex_x * (texture->bits_per_pixel / 8)));
		my_mlx_pixel_put(&root->mlx_img, strip_id, y++, color);
		tex_pos += tex_step;
	}

}


// void	render_wall(t_root *root, t_ray *ray,int strip_id, float anglee)
// {
// 	int			tex_x;
// 	int			tex_y;
// 	float		tex_step;
// 	float		tex_pos;
// 	int			y;
// 	t_mlx		*texture;
// 	t_rndr_str	*rndr;

// 	rndr = crt_rnd_str(root, ray, anglee, &texture);
// 	if (!rndr)
// 		return;
// 	y = 0;
// 	tex_x = (int)(rndr->wall_x * texture->width / TILE_SIZE);
// 	if (tex_x < 0)
// 		tex_x = 0;
// 	if (tex_x >= texture->width)
// 		tex_x = texture->width - 1;
// 	tex_step = (float)texture->height / rndr->wallstripeheight;
// 	tex_pos = 0;
// 	while ( y < rndr->walltoppixel)
// 		my_mlx_pixel_put(&root->mlx_img, strip_id, y++, BLUE);
// 	y = rndr->walltoppixel;
// 	while (y < rndr->wallbottompixel)
// 	{
// 		tex_y = (int)tex_pos;
// 		if (tex_y >= texture->height)
// 			tex_y = texture->height - 1;
// 		int color = *(int *)(texture->addr + (tex_y * texture->line_length + tex_x * (texture->bits_per_pixel / 8)));
// 		my_mlx_pixel_put(&root->mlx_img, strip_id, y++, color);
// 		tex_pos += tex_step;
// 	}
// 	y = rndr->wallbottompixel;
// 	while (y < root->win_h)
// 		my_mlx_pixel_put(&root->mlx_img, strip_id, y++, GREEN);
// 	free(rndr);
// }

void draw_wall_strip(t_root *root, t_rndr_str *rndr, int strip_id, t_mlx *texture)
{
	float		tex_x;
	float		tex_y;
	float	tex_step;
	float	tex_pos;
	int		y;

	tex_x = (int)(rndr->wall_x * texture->width / TILE_SIZE);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= texture->width)
		tex_x = texture->width - 1;
	tex_step = (float)texture->height / rndr->wallstripeheight;
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
		int color = *(int *)(texture->addr + (int)(tex_y * texture->line_length + tex_x * (texture->bits_per_pixel / 8)));
		my_mlx_pixel_put(&root->mlx_img, strip_id, y++, color);
		tex_pos += tex_step;
	}
	y = rndr->wallbottompixel;
	while (y < root->win_h)
		my_mlx_pixel_put(&root->mlx_img, strip_id, y++, GREEN);
}

void render_wall(t_root *root, t_ray *ray, int strip_id, float anglee)
{
	t_mlx		*texture;
	t_rndr_str	*rndr;

	rndr = crt_rnd_str(root, ray, anglee, &texture);
	if (!rndr)
		return;
	draw_wall_strip(root, rndr, strip_id, texture);
	free(rndr);
}

// void render_wall(t_root *root, t_ray *ray, int strip_id, float anglee)
// {
// 	float perp_dist;
// 	float distanceprojwall;
// 	float projwallheight;
// 	int wallstripeheight;
// 	int wallbottompixel;
// 	int walltoppixel;
// 	int y;
// 	int tex_x;
// 	int tex_y;
// 	float tex_step;
// 	float tex_pos;
// 	float wall_x;
// 	t_mlx *texture;

// 	perp_dist = ray->distance * cos((double)(anglee - root->player->rot_angl));
// 	distanceprojwall = (root->win_w / 2) / tan(FOV / 2);
// 	projwallheight = (TILE_SIZE / perp_dist) * distanceprojwall;
// 	wallstripeheight = (int)projwallheight;
// 	walltoppixel = (root->win_h / 2) - (wallstripeheight / 2);
// 	wallbottompixel = (root->win_h / 2) + (wallstripeheight / 2);
// 	if (walltoppixel < 0)
// 		walltoppixel = 0;
// 	if (wallbottompixel > root->win_h)
// 		wallbottompixel = root->win_h;
// 	if ( ray->wallhitvertical)
// 	{
// 		if (ray->facingleft)
// 			texture = &root->left_wall_texture;
// 		else
// 			texture = &root->right_wall_texture;
// 		wall_x = ray->wallhity - floor(ray->wallhity / TILE_SIZE) * TILE_SIZE;
// 	}
// 	else
// 	{
// 		if (ray->facingup)
// 			texture = &root->front_wall_texture;
// 		else
// 			texture = &root->back_wall_texture;
// 		wall_x = ray->wallhitx - floor(ray->wallhitx / TILE_SIZE) * TILE_SIZE;
// 	}
// 	// gggjgjfdfhjkhfdkfhdfhkffhkh
// 	tex_x = (int)(wall_x * texture->width / TILE_SIZE);
// 	if (tex_x < 0)
// 		tex_x = 0;
// 	if (tex_x >= texture->width)
// 		tex_x = texture->width - 1;
// 	tex_step = (float)texture->height / wallstripeheight;
// 	tex_pos = 0;
// 	y = 0;
// 	while (y < walltoppixel)
// 		my_mlx_pixel_put(&root->mlx_img, strip_id, y++, BLUE);
// 	y = walltoppixel;
// 	while (y < wallbottompixel)
// 	{
// 		tex_y = (int)tex_pos;
// 		if (tex_y >= texture->height)
// 			tex_y = texture->height - 1;
// 		int color = *(int *)(texture->addr + (tex_y * texture->line_length + tex_x * (texture->bits_per_pixel / 8)));
// 		my_mlx_pixel_put(&root->mlx_img, strip_id, y++, color);
// 		tex_pos += tex_step;
// 	}
// 	y = wallbottompixel;
// 	while (y < root->win_h)
// 		my_mlx_pixel_put(&root->mlx_img, strip_id, y++, GREEN);
// }
