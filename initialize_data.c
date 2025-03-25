/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-garr <ael-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 15:16:25 by ael-garr          #+#    #+#             */
/*   Updated: 2025/03/24 21:18:27 by ael-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

int	find_the_longest_line(char **map)
{
	int		i;
	size_t	max;

	i = 0;
	if (!map)
		return (0);
	max = ft_strlen1(map[0]);
	while (map[i])
	{
		if (ft_strlen1(map[i]) > max)
			max = ft_strlen1(map[i]);
		i++;
	}
	return (max);
}

void	initialize_data(t_root *root, t_params *params, t_player *player)
{
	if (!params || !player || !root)
		return ;
	root->player = player;
	root->mlx = mlx_init();
	root->map = params->map;
	immegrate_map(&root->map, &params->map);
	root->map_h = params->map_height;
	root->map_w = find_the_longest_line(params->map);
	root->win_w = root->map_w * TILE_SIZE;
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
