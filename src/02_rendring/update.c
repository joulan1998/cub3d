/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-garr <ael-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 17:03:29 by ael-garr          #+#    #+#             */
/*   Updated: 2025/03/18 15:59:06 by ael-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../headers/cub3d.h"

void	update(t_root **root)
{
	render_map(*root);
	render_player(*root);
	render_dir(*root);
	cast_allrays(*root);
	mini_map(root);
	mlx_put_image_to_window((*root)->mlx, (*root)->win,
		(*root)->mlx_img.img, 0, 0);
}
