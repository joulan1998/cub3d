/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-garr <ael-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 15:16:25 by ael-garr          #+#    #+#             */
/*   Updated: 2025/03/18 15:59:06 by ael-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../headers/cub3d.h"

// todo: change this fucntion to bool incase something happens it should return false otherwise return true
void	initialize_data(t_root *root, t_params *params, t_player *player)
{
	if (!params || !player || !player)
		return ;
	root->player = player;
	root->mlx = mlx_init();
	root->map = params->map; // this might not work, so we need a new function to move it from there to here
	root->map_h = params->map_height;
	root->map_w = params->map_width;
	root->win_w = root->map_w * TILE_SIZE; // might become problematic if we give it a big map
	root->win_h = root->map_h * TILE_SIZE;
	root->floor_color = params->floor_color; 
	root->ceiling_color = params->ceiling_color;
	root->win = mlx_new_window(root->mlx, root->win_w, root->win_h, "cub3D");
	root->mlx_img.img = mlx_new_image(root->mlx, root->win_w, root->win_h);
	root->mlx_img.addr = mlx_get_data_addr
		(root->mlx_img.img, &root->mlx_img.bits_per_pixel,
			&root->mlx_img.line_length, &root->mlx_img.endian);
	load_xpm_texture(root->mlx, params->no_texture, &root->mlx_no_texture);
	load_xpm_texture(root->mlx, params->so_texture, &root->mlx_so_texture);
	load_xpm_texture(root->mlx, params->we_texture, &root->mlx_we_texture);
	load_xpm_texture(root->mlx, params->ea_texture, &root->mlx_ea_texture);
}
