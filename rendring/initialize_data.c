/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-garr <ael-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 15:16:25 by ael-garr          #+#    #+#             */
/*   Updated: 2025/03/16 16:57:09 by ael-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	initialize_data(t_root *root, char ***map, t_player *player)
{
	if (!map || !*map || !player || !player)
		return ;
	root->player = player;
	root->mlx = mlx_init();
	root->map = malloc(sizeof(char **));
	root->map = *map;
	root->map_h = count_lines(*map);
	root->map_w = ft_strlen(root->map[0]);
	root->win_w = root->map_w * TILE_SIZE;
	root->win_h = root->map_h * TILE_SIZE;
	root->win = mlx_new_window(root->mlx, root->win_w, root->win_h, "cub3D");
	root->mlx_img.img = mlx_new_image(root->mlx, root->win_w, root->win_h);
	root->mlx_img.addr = mlx_get_data_addr
		(root->mlx_img.img, &root->mlx_img.bits_per_pixel,
			&root->mlx_img.line_length, &root->mlx_img.endian);
	load_xpm_texture(root->mlx, "wall_s.xpm", &root->front_wall_texture);
	load_xpm_texture(root->mlx, "wall_s.xpm", &root->back_wall_texture);
	load_xpm_texture(root->mlx, "wall.xpm", &root->left_wall_texture);
	load_xpm_texture(root->mlx, "wall.xpm", &root->right_wall_texture);
}
