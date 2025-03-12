/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendring_walls.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-garr <ael-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 16:23:34 by ael-garr          #+#    #+#             */
/*   Updated: 2025/03/12 16:42:33 by ael-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	render_wall(t_root *root, t_ray *ray, int strip_id, float anglee)
{
	float	perp_dist;
	float	distanceprojwall;
	float	projwallheight;
	int		wallstripeheight;
	int		wallbottompixel;
	int		walltoppixel;
	int		y;

	perp_dist = ray->distance * cos((double)(anglee - root->player->rot_angl));
	distanceprojwall = (root->win_w / 2) / tan(FOV / 2);
	projwallheight = (TILE_SIZE / perp_dist) * distanceprojwall;
	wallstripeheight = (int)projwallheight;
	walltoppixel = (root->win_h / 2) - (wallstripeheight / 2);
	wallbottompixel = (root->win_h / 2) + (wallstripeheight / 2);
	if (walltoppixel < 0)
		walltoppixel = 0;
	if (wallbottompixel > root->win_h)
		wallbottompixel = root->win_h;
	y = 1;
	while (y < walltoppixel)
	{
		my_mlx_pixel_put(&root->mlx_img, strip_id, y, BLUE);
		y++;
	}
	y = walltoppixel;
	while (y < wallbottompixel)
	{
		// if ((!(y %10) && !(y%40)) || (!(strip_id % 10) && !(strip_id % 40)))
		if (!(strip_id % 10) && !(strip_id % 40))
			my_mlx_pixel_put(&root->mlx_img, strip_id, y, RED);
		else
			my_mlx_pixel_put(&root->mlx_img, strip_id, y, WHITE);
		y++;
	}
	y = wallbottompixel;
	while (y < root->win_h)
	{
		my_mlx_pixel_put(&root->mlx_img, strip_id, y++, GREEN);
	}
}
