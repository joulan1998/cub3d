/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-garr <ael-garr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 17:03:29 by ael-garr          #+#    #+#             */
/*   Updated: 2025/03/26 10:48:39 by ael-garr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	update(t_root **root)
{
	int	rays_nbr;

	rays_nbr = ((*root)->map_w * TILE_SIZE) / WALL_STRIPE;
	cast_allrays(*root, rays_nbr);
	mini_map(root);
	mlx_put_image_to_window((*root)->mlx, (*root)->win,
		(*root)->mlx_img.img, 0, 0);
}

float	set_rota_angle(char dir)
{
	if (dir == 'N')
		return (-(M_PI / 2));
	else if (dir == 'S')
		return (M_PI / 2);
	else if (dir == 'W')
		return (0);
	else
		return (-M_PI);
}

char	find_p_sym(char **map)
{
	int	i;

	i = 0;
	while (i < count_lines(map))
	{
		if (ft_strchr1(map[i], 'N') != 0)
			return ('N');
		else if (ft_strchr1(map[i], 'E') != 0)
			return ('E');
		else if (ft_strchr1(map[i], 'S') != 0)
			return ('S');
		else if (ft_strchr1(map[i], 'W') != 0)
			return ('W');
		i++;
	}
	return ('N');
}
