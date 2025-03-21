/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-garr <ael-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 15:16:25 by ael-garr          #+#    #+#             */
/*   Updated: 2025/03/21 17:08:04 by ael-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"



void	initialize_data(t_root *root, t_params *params, t_player *player)
{
	if (!params || !player || !root)
		return ;
	root->player = player;
	root->mlx = mlx_init();
	root->map = params->map; // this might not work, so we need a new function to move it from there to here
	root->map_h = 7;
	// root->map_h = params->map_height;
	// root->map_w = params->map_width; // set it to the actual function
	root->map_w = 33; // set it to the actual function 
	printf("the win_h is %zu\n", root->map_w);
	root->win_w = root->map_w * TILE_SIZE; // might become problematic if we give it a big map
	root->win_h = root->map_h * TILE_SIZE;
	root->floor_color = params->floor_color; 
	root->ceiling_color = params->ceiling_color;
	root->win = mlx_new_window(root->mlx, root->win_w, root->win_h, "cub3D");
	root->mlx_img.img = mlx_new_image(root->mlx, root->win_w, root->win_h);
	root->mlx_img.addr = mlx_get_data_addr
		(root->mlx_img.img, &root->mlx_img.bits_per_pixel,
			&root->mlx_img.line_length, &root->mlx_img.endian);
	load_xpm_texture(root->mlx, params->no_texture, &root->front_wall_texture);
	load_xpm_texture(root->mlx, params->so_texture, &root->back_wall_texture);
	load_xpm_texture(root->mlx, params->we_texture, &root->left_wall_texture);
	load_xpm_texture(root->mlx, params->ea_texture, &root->right_wall_texture);
}
// void	initialize_data(t_root *root, t_params *params, char ***map, t_player *player)
// {
// 	if (!map || !*map || !player || !player)
// 		return ;
// 	root->player = player;
// 	root->mlx = mlx_init();
// 	root->map = malloc(sizeof(char **));
// 	root->map = *map;
// 	root->map_h = count_lines(*map);
// 	root->map_w = ft_strlen(root->map[0]);
// 	root->win_w = root->map_w * TILE_SIZE;
// 	root->win_h = root->map_h * TILE_SIZE;
// 	root->win = mlx_new_window(root->mlx, root->win_w, root->win_h, "cub3D");
// 	root->mlx_img.img = mlx_new_image(root->mlx, root->win_w, root->win_h);
// 	root->mlx_img.addr = mlx_get_data_addr
// 		(root->mlx_img.img, &root->mlx_img.bits_per_pixel,
// 			&root->mlx_img.line_length, &root->mlx_img.endian);
// 	load_xpm_texture(root->mlx, "wall_s.xpm", &root->front_wall_texture);
// 	load_xpm_texture(root->mlx, "wall_s.xpm", &root->back_wall_texture);
// 	load_xpm_texture(root->mlx, "wall.xpm", &root->left_wall_texture);
// 	load_xpm_texture(root->mlx, "wall.xpm", &root->right_wall_texture);
// }
