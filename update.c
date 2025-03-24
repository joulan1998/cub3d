/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-garr <ael-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 17:03:29 by ael-garr          #+#    #+#             */
/*   Updated: 2025/03/24 13:27:50 by ael-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	update(t_root **root)
{
	int rays_nbr;

	rays_nbr = ((*root)->map_w * TILE_SIZE ) / WALL_STRIPE ;
	render_map(*root);
	// render_dir(*root);
	// render_player(root);
	// cast_allrays(*root, ((*root)->map_w * TILE_SIZE ) / WALL_STRIPE );
	cast_allrays(*root, rays_nbr); /// hare  it is
	mini_map(root);
	// exit(22);
	mlx_put_image_to_window((*root)->mlx, (*root)->win, (*root)->mlx_img.img, 0, 0);
}
